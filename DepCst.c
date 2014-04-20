//inter-statment dep; -Ci+C'i' >= 0
static PlutoConstraints *get_legality_constraints_nonuniform_dep(Dep *dep, const PlutoProg *prog)   
{
    PlutoConstraints *cst;
    int nvar = prog->nvar;
    int npar = prog->npar;
    
    PlutoConstraints *dpoly = pluto_constraints_to_pure_inequalities(dep->dpolytope);
    
    int dnrows = dpoly->nrows;

    cst = pluto_constraints_alloc(MAX_FARKAS_CST, 2*(nvar+1)+dnrows+2);
    cst->nrows = 2*nvar+npar+1+1+dnrows+1;    // Ci | C'i | P | const | sigma | lambda
    cst->ncols = 2*(nvar+1)+dnrows+2;   // Ci | C'i | lambda | const

    for(int i = 0; i < cst->ncols; i++)
        for(int j = 0; j < cst->nrows; j++)
            cst->val[i][j] = 0;


    for(int i = 0; i < nvar; i++)   //ci = xxxx
    {
        cst->val[i][i] = -1;
        for(int j = 0; j < dnrows; j++)
            cst->val[i][2*nvar+2+j] = -dpoly->val[j][i];
    }

    for(int i = 0; i < nvar; i++)   //ci' = xxx
    {
        int oi = i + nvar;
        cst->val[oi][oi+1] = 1;
        for(int j = 0; j < dnrows; j++){
            int oj = j+2*nvar+2;
            cst->val[oi][oj] = -dpoly->val[j][oi];
        }
    }

    for(int i = 0; i < npar; i++) // 0 = xxx
    {
        int oi = i + 2*nvar;
        for(int j = 0; j < dnrows; j++){
            cst->val[oi][2*nvar+2+i] = -dpoly[j][oi];
        }
    }

    //constant: -c0+c0'=xxx+lambda0
    int offsetRow=0;   //lamda_0
    cst->val[constPos][nvar] = -1;
    cst->val[constPos][2*nvar+1] = 1;
    cst->val[constPos][2(nvar+1)+dnrows]=-1;
    for(int i = 0; i < dnrows; i++)
        cst->val[constPos][2*(nvar+1)+i] -= dpoly->val[i][2*nvar+npar];

    //-Ci+C'i'=lamda*dep
    constPos++;
    for(int i = 0; i < cst->ncols; i++)
        for(int j = 2*nvar+npar; j >= 0; j--)
            cst->val[constPos][i] -= cst->val[j][i];

    //lamda>=0
    constPos++;
    for(int i = 0; i < dnrows; i++) //xi>=0
    {
        int oj = 2*(nvar+1);
        cst->val[constPos+i][oj+i]=1;
    }
    eliminate_farkas_multipliers(cst, cst->ncols-2*(nvar+1)-1);
}

//inter-statment constraints for Ci - C'i' + vp >= 0
static PlutoConstraints *get_localilty_constraints_nonuniform_dep(Dep *dep, const PlutoProg *prog)
{
    PlutoConstraints *cst;
    int nvar = prog->nvar;
    int npar = prog->nvar;
    
    PlutoConstraints *dploy = pluto_constraints_to_pure_inequalities(dep);
    int dnrows = dploy->nrwos;

    cst = pluto_constraints_alloc(MAX_FARKAS_CST, );
    cst->nrows = 2*nvar+npar+1+1+dnrows+1;  //Ci | C'i | v(P) | const | sigma | lambda 
    cst->ncols = npar+1+2*(nvar+1)+dnrows+1+1;  // P | w | Ci+C0 | C'i+C0 | lambda | const

    for(int i = 0; i < cst->ncols; i++)
        for(int j = 0; j < cst->nrwos; j++)
            cst[i][j] = 0;

    int ocl = npar+1+2*(nvar+1);   //offset for column of lambda
    int occ = npar+1;   //offset  for column of C 
    //ci = xxx
    for(int i = 0; i < nvar; i++)
    {
        cst->val[i][occ+i] = 1;
        for(int j = 0; j < dnrows; j++)
            cst->val[i][j+ocl] = -dpoly->val[j][i];
    }

    //-c'i' = xxx
    for(int i = 0; i < nvar; i++)
    {
        int oi = i + nvar;
        cst->val[oi][occ+(nvar+1)+i] = -1;
        for(int j = 0; j < dnrows; j++)
            cst->val[oi][j+ocl] = -dpoly->val[j][oi];
    }

    //-vp=...
    for(int i = 0; i < npar; i++)
    {
        int oi = i + 2*nvar;
        cst->val[oi][i] = 1;
        for(int j = 0; j < dnrows; j++)
            cst->val[oi][j+ocl] = -dpoly->val[oi];
    }

    //const: c0-c0'+w=...
    int offsetRow=2*nvar+npar;
    cst->val[offsetRow][occ+nvar]=1;
    cst->val[offsetRow][occ+nvar+1+nvar]=-1;
    cst->val[offsetRow][npar]=1;
    for(int i = 0; i < dnrows; j++)
        cst->val[offsetRow][i+ocl] = -dpoly->val[i][2*nvar+npar];

    //sigma
    offsetRow++;
    for(int i = 0; i < cst->ncols; i++)
        for(int j = 0; j < offsetRow; j++)
            cst->val[offsetRow][i] -= cst->val[j][i];
    //lambda
    offsetRow++;
    for(int i = 0; i < dnrows+1; i++)
        cst->val[offsetRow+i][ocl+i]=1;
    eliminate_farkas_multipliers(cst, cst->ncols-(npar+1)-2*(nvar+1));
}

//inter-statment constraints for UB - (c'i'-ci) -vp >= 0, UB is the upper bounding for (c'i' - ci)
static PlutoConstraints *get_minuseless_constraints_nonuniform_dep(Dep *dep1, int* UB const PlutoProg *prog)
{
    //UB = | P | C |
    PlutoConstraints *cst;
    int nvar = prog->nvar;
    int npar = prog->nvar;
    
    PlutoConstraints *dploy = pluto_constraints_to_pure_inequalities(dep);
    int dnrows = dploy->nrwos;

    cst = pluto_constraints_alloc(MAX_FARKAS_CST, );
    cst->nrows = 2*nvar+npar+1+1+dnrows+1;  //Ci | C'i | v(P) | const | sigma | lambda 
    cst->ncols = npar+1+2*(nvar+1)+dnrows+1+1;  // v | w | Ci+C0 | C'i+C0 | lambda | const

    for(int i = 0; i < cst->ncols; i++)
        for(int j = 0; j < cst->nrwos; j++)
            cst[i][j] = 0;

    int ocl = npar+1+2*(nvar+1);   //offset for column of lambda
    int occ = npar+1;   //offset  for column of C 

    //ci = xxx
    for(int i = 0; i < nvar; i++)
    {
        cst->val[i][occ+i] = 1;
        for(int j = 0; j < dnrows; j++)
            cst->val[i][j+ocl] = -dpoly->val[j][i];
    }

    //-c'i' = xxx
    for(int i = 0; i < nvar; i++)
    {
        int oi = i + nvar;
        cst->val[oi][occ+(nvar+1)+i] = -1;
        for(int j = 0; j < dnrows; j++)
            cst->val[oi][j+ocl] = -dpoly->val[j][oi];
    }

    //-vp=...
    for(int i = 0; i < npar; i++)
    {
        int oi = i + 2*nvar;
        cst->val[oi][i] = 1;
        cst->val[oi][cst->ncols-1] = UB[i];
        for(int j = 0; j < dnrows; j++)
            cst->val[oi][j+ocl] -= dpoly->val[oi];
    }

    //const: c0-c0'+w=...
    int offsetRow=2*nvar+npar;
    cst->val[offsetRow][occ+nvar]=1;
    cst->val[offsetRow][occ+nvar+1+nvar]=-1;
    cst->val[offsetRow][npar]=1;
    cst->val[offsetRow][cst->ncols-1]=UB[npar];
    for(int i = 0; i < dnrows; j++)
        cst->val[offsetRow][i+ocl] -= dpoly->val[i][2*nvar+npar];

    //sigma
    offsetRow++;
    for(int i = 0; i < cst->ncols; i++)
        for(int j = 0; j < offsetRow; j++)
            cst->val[offsetRow][i] -= cst->val[j][i];
    //lambda
    offsetRow++;
    for(int i = 0; i < dnrows+1; i++)
        cst->val[offsetRow+i][ocl+i]=1;
    eliminate(cst, cst->ncols-(npar+1)-2*(nvar+1)-1);
}

static PlutoConstraints *get_permutability_constraints_nonuniform_dep(Dep *dep, const PlutoProg *prog)
{
    PlutoConstraints *farkas_cst, *comm_farkas_cst, *cst;
    int src_stmt, dest_stmt, j, k;
    int src_offset, dest_offset;

    int nvar = prog->nvar;
    int npar = prog->npar;
    Stmt **stmts = prog->stmts;
    int nstmts = prog->nstmts;

    dest_stmt = dep->dest;
    src_stmt = dep->src;

    /* Convert everything to >= 0 form */
    PlutoConstraints *dpoly = pluto_constraints_to_pure_inequalities(dep->dpolytope);

    /* Non-uniform dependence - farkas lemma comes in */
    /* Apply farkas lemma, eliminate farkas multipliers using
     * fourier-motzkin 
     * 
     * -- farkas_cst format for legality --
     * [ mapping coeff for src | ... for dest |farkas multipliers|constant]
     * SIZE: [nvar+1 | nvar+1 | dep.dpolytope->nrows+1 | 1]
     *
     * -- farkas_cst format for bounding function --
     * [bounding func | mapping coeff for src | ... for dest |farkas multipliers|constant]
     * SIZE: [npar+1| nvar+1 | nvar+1 | dep.dpolytope->nrows+1 | 1]
     *
     */
    if (src_stmt != dest_stmt)  {
        /* Inter-statement non-uniform dep */
        farkas_cst = pluto_constraints_alloc(MAX_FARKAS_CST, 2*nvar+2+dpoly->nrows+2);
        comm_farkas_cst = pluto_constraints_alloc(MAX_FARKAS_CST, npar+1+2*nvar+2+dpoly->nrows+2);

        farkas_cst->nrows = (2*nvar+npar+1)+1+dpoly->nrows+1;
        farkas_cst->ncols = 2*(nvar+1)+dpoly->nrows+2;

        comm_farkas_cst->nrows = (2*nvar+npar+1)+1+dpoly->nrows+1;
        comm_farkas_cst->ncols = npar+1+2*(nvar+1)+dpoly->nrows+2;
    }else{
        /* Intra-statement non-uniform dependence */
        farkas_cst = pluto_constraints_alloc(MAX_FARKAS_CST, nvar+1+dpoly->nrows+2);
        comm_farkas_cst = pluto_constraints_alloc(MAX_FARKAS_CST, npar+1+nvar+1+dpoly->nrows+2);

        farkas_cst->nrows = (2*nvar+npar+1)+1+dpoly->nrows+1;
        farkas_cst->ncols = (nvar+1)+dpoly->nrows+2;

        comm_farkas_cst->nrows = (2*nvar+npar+1)+1+dpoly->nrows+1;
        comm_farkas_cst->ncols = npar+1+(nvar+1)+dpoly->nrows+2;
    }


    /* Initialize all to zero */
    for (j=0; j<farkas_cst->nrows; j++)  {
        for (k=0; k<farkas_cst->ncols; k++)  {
            farkas_cst->val[j][k] = 0;
        }
    }

    for (j=0; j<comm_farkas_cst->nrows; j++)  {
        for (k=0; k<comm_farkas_cst->ncols; k++)  {
            comm_farkas_cst->val[j][k] = 0;
        }
    }

    if (src_stmt != dest_stmt)  {

        /* Add tiling legality constraints */
        for (j=0; j<2*nvar+npar+1; j++)  {
            if (j < nvar)   {
                /* src stmt coeff */
                farkas_cst->val[j][j] = -1;
            }else if (j < 2*nvar)   {
                /* dest stmt coeff */
                farkas_cst->val[j][j+1] = 1;
            }else if (j < 2*nvar+npar)  {
                /* Do nothing - all coeff multipliers stay zero */
                /* since structure parameters not in our affine mappings */
            }else{
                /* j = 2*nvar+npar */
                /* Translation coefficients in the affine mappings */
                farkas_cst->val[j][nvar] = -1;
                farkas_cst->val[j][2*nvar+1] = 1;
                /* \lambda_0 */
                farkas_cst->val[j][farkas_cst->ncols-2] = -1;
            } 

            /* Set coeff's for farkas multipliers (all except \lambda_0) */
            for (k=2*nvar+2; k<2*nvar+2+dpoly->nrows; k++)  {
                /* Note that dep polytope is dpolytope->nrows x (2*nvar+npar+1) */
                farkas_cst->val[j][k] = -dpoly->val[k-2*nvar-2][j];
            }
            farkas_cst->val[j][farkas_cst->ncols-1] = 0;
        }

        /* Since the above are equalities - add sigma negative */
        for (k=0; k<farkas_cst->ncols; k++)    {
            farkas_cst->val[2*nvar+npar+1][k] = 0;
            for (j=0; j<2*nvar+npar+1; j++)  {
                farkas_cst->val[2*nvar+npar+1][k] -= farkas_cst->val[j][k];
            }
        }

        /* All Farkas multipliers are non-negative */
        for (j=0; j<dpoly->nrows+1; j++)  {
            for (k=0; k<dpoly->nrows+1; k++)  {
                farkas_cst->val[2*nvar+npar+2+j][2*nvar+2+k] = ((j==k)?1:0);
            }
        }

        /* Bounding function constraints */
        for (k=0; k<npar; k++)  {
            comm_farkas_cst->val[2*nvar+k][k] = 1;
        }

        comm_farkas_cst->val[2*nvar+npar][npar] = 1;

        for (j=0; j<2*nvar+npar+1; j++)
            for (k=0; k<farkas_cst->ncols-dpoly->nrows-2; k++)
                comm_farkas_cst->val[j][npar+1+k] = -farkas_cst->val[j][k];

        for (j=0; j<2*nvar+npar+1; j++)
            for (k=farkas_cst->ncols-dpoly->nrows-2; k<farkas_cst->ncols; k++)
                comm_farkas_cst->val[j][npar+1+k] = farkas_cst->val[j][k];

        /* Add opp inequality since the above were equalities */
        for (k=0; k<comm_farkas_cst->ncols; k++)    {
            comm_farkas_cst->val[2*nvar+npar+1][k] = 0;
            for (j=0; j<2*nvar+npar+1; j++) {
                comm_farkas_cst->val[2*nvar+npar+1][k] -= comm_farkas_cst->val[j][k];
            }
        }

        for (j=2*nvar+npar+2; j<farkas_cst->nrows; j++)
            for (k=0; k<farkas_cst->ncols; k++)
                comm_farkas_cst->val[j][npar+1+k] = farkas_cst->val[j][k];
        
        eliminate_farkas_multipliers(farkas_cst, farkas_cst->ncols-2*nvar-3);
        eliminate_farkas_multipliers(comm_farkas_cst, comm_farkas_cst->ncols-npar-1-2*nvar-3);

        /* constraints_print(stdout, farkas_cst); */

    }else{
        /* Source stmt == Dest stmt */

        for (j=0; j<2*nvar+npar+1; j++)  {
            if (j < nvar)   {
                /* src stmt coeff */
                farkas_cst->val[j][j] = -1;
            }else if (j < 2*nvar)   {
                /* dest stmt coeff */
                farkas_cst->val[j][j-nvar] = 1;
            }else if (j < 2*nvar+npar)  {
                /* Do nothing - all coeff multipliers stay zero */
                /* NOTE: structure parameters not in our affine mappings */
            }else{
                /* Translation coefficient gets subtracted out */
                farkas_cst->val[j][nvar] = 0;
                farkas_cst->val[j][farkas_cst->ncols-2] = -1;
            } 

            /* Set coeff's for farkas multipliers */
            for (k=nvar+1; k<nvar+1+dpoly->nrows; k++)  {
                farkas_cst->val[j][k] = -dpoly->val[k-nvar-1][j];
            }
            farkas_cst->val[j][farkas_cst->ncols-1] = 0;
        }

        /* Since the above are equalities - add sigma negative */
        for (k=0; k<farkas_cst->ncols; k++)    {
            farkas_cst->val[2*nvar+npar+1][k] = 0;
            for (j=0; j<2*nvar+npar+1; j++)  {
                farkas_cst->val[2*nvar+npar+1][k] -= farkas_cst->val[j][k];
            }
        }

        /* All farkas multipliers are positive */
        for (j=0; j<dpoly->nrows+1; j++)  {
            for (k=0; k<dpoly->nrows+1; k++)  {
                farkas_cst->val[2*nvar+npar+2+j][nvar+1+k] = ((j==k)?1:0);
            }
        }

        /* Bounding function constraints */
        for (k=0; k<npar; k++)  {
            comm_farkas_cst->val[2*nvar+k][k] = 1;
        }

        comm_farkas_cst->val[2*nvar+npar][npar] = 1;

        for (j=0; j<2*nvar+npar+1; j++)
            for (k=0; k<farkas_cst->ncols-dpoly->nrows-2; k++)
                comm_farkas_cst->val[j][npar+1+k] = -farkas_cst->val[j][k];

        for (j=0; j<2*nvar+npar+1; j++)
            for (k=farkas_cst->ncols-dpoly->nrows-2; k<farkas_cst->ncols; k++)
                comm_farkas_cst->val[j][npar+1+k] = farkas_cst->val[j][k];

        /* Add opp inequality since the above were equalities */
        for (k=0; k<comm_farkas_cst->ncols; k++)    {
            comm_farkas_cst->val[2*nvar+npar+1][k] = 0;
            for (j=0; j<2*nvar+npar+1; j++) {
                comm_farkas_cst->val[2*nvar+npar+1][k] -= comm_farkas_cst->val[j][k];
            }
        }

        for (j=2*nvar+npar+2; j<farkas_cst->nrows; j++)
            for (k=0; k<farkas_cst->ncols; k++)
                comm_farkas_cst->val[j][npar+1+k] = farkas_cst->val[j][k];

        eliminate_farkas_multipliers(farkas_cst, farkas_cst->ncols-nvar-2);
        eliminate_farkas_multipliers(comm_farkas_cst, comm_farkas_cst->ncols-npar-1-nvar-2);

        /* constraints_print(stdout, farkas_cst); */
    }

    /* Aggregate permutability and bounding function constraints together in
     * global format format */

    /* Initialize everything to zero */
    cst = pluto_constraints_alloc(farkas_cst->nrows + comm_farkas_cst->nrows, CST_WIDTH);
    cst->ncols = CST_WIDTH;

    for (k=0; k<farkas_cst->nrows+comm_farkas_cst->nrows; k++)   {
        for (j=0; j<cst->ncols; j++)  {
            cst->val[k][j] = 0;
        }
    }

    src_offset = npar+1+src_stmt*(nvar+1);
    dest_offset = npar+1+dest_stmt*(nvar+1);

    /* Permutability constraints */
    if (!IS_RAR(dep->type)) {
        for (k=0; k<farkas_cst->nrows; k++)   {
            for (j=0; j<nvar+1; j++)  {
                cst->val[cst->nrows+k][src_offset+j] = farkas_cst->val[k][j];
                if (src_stmt != dest_stmt) {
                    cst->val[cst->nrows+k][dest_offset+j] = farkas_cst->val[k][nvar+1+j];
                }
            }
            /* constant part */
            if (src_stmt == dest_stmt)  {
                cst->val[cst->nrows+k][cst->ncols-1] = farkas_cst->val[k][nvar+1];
            }else{
                cst->val[cst->nrows+k][cst->ncols-1] = farkas_cst->val[k][2*nvar+2];
            }
        }
        cst->nrows = farkas_cst->nrows;
    }

    if (!options->nobound)   {
        /* Add bounding constraints */
        src_offset = npar+1+src_stmt*(nvar+1);
        dest_offset = npar+1+dest_stmt*(nvar+1);

        for (k=0; k<comm_farkas_cst->nrows; k++)   {
            for (j=0; j<npar+1; j++)  {
                cst->val[cst->nrows+k][j] = comm_farkas_cst->val[k][j];
            }
            for (j=0; j<nvar+1; j++)  {
                cst->val[cst->nrows+k][src_offset+j] = comm_farkas_cst->val[k][npar+1+j];
                if (src_stmt != dest_stmt) cst->val[cst->nrows+k][dest_offset+j] = comm_farkas_cst->val[k][npar+1+nvar+1+j];
            }
            /* constant part */
            if (src_stmt == dest_stmt)  {
                cst->val[cst->nrows+k][cst->ncols-1] = comm_farkas_cst->val[k][npar+1+nvar+1];
            }else{
                cst->val[cst->nrows+k][cst->ncols-1] = comm_farkas_cst->val[k][npar+1+2*nvar+2];
            }
        }
        cst->nrows += comm_farkas_cst->nrows;
    }


    /* Coefficients of those variables that don't appear in the outer loop
     * are useless */
    for (k=0; k<nvar; k++)    {
        if (!stmts[src_stmt]->is_orig_loop[k])  {
            for (j=0; j < cst->nrows; j++)   {
                cst->val[j][src_offset+k] = 0;
            }
        }
        if (src_stmt != dest_offset && !stmts[dest_stmt]->is_orig_loop[k])  {
            for (j=0; j < farkas_cst->nrows+comm_farkas_cst->nrows; j++)   {
                cst->val[j][dest_offset+k] = 0;
            }
        }
    }

    pluto_constraints_free(farkas_cst);
    pluto_constraints_free(comm_farkas_cst);
    pluto_constraints_free(dpoly);

    return cst;
}

static PlutoConstraints *get_permutability_constraints_each_dep(Dep *dep, const PlutoProg *prog)
{
    PlutoConstraints *legality = get_legality_constraints_nonuniform_dep(dep, prog);
    PlutoConstraints *locality = get_localilty_constraints_nonuniform_dep(dep, prog);
    PlutoConstraints *total = pluto_constraints_alloc(legality->nrows+locality->nrows, CST_WIDTH);

    pluto_constraints_add(total, legality);
    pluto_constraints_add(total, locality);

    
}