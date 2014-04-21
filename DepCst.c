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

//Find constraints for a dep, and return the independent constraints for it
static PlutoConstraints *get_permutability_constraints_each_dep(Dep *dep, const PlutoProg *prog){
    PlutoConstraints *legality = get_legality_constraints_nonuniform_dep(dep, prog);
    PlutoConstraints *locality = get_localilty_constraints_nonuniform_dep(dep, prog);
    PlutoConstraints *total = pluto_constraints_alloc(legality->nrows+locality->nrows, CST_WIDTH);

    pluto_constraints_add(total, legality);
    pluto_constraints_add(total, locality);

    return total;
}

static void get_permutability_constraints(const PlutoProg *prog){
    Dep **deps = prog->degs;
    PlutoConstraints *total;
    PlutoConstraints **depcst;
    
    depcst = prog->depcst;
    if(depcst == NULL){
        depcst = (PlutoConstraints**)malloc(prog->ndeps * sizeof(PlutoConstraints*));
        for(int i = 0; i < prog->ndeps; i++)
            depcst[i] = NULL;
    }

    int total_rows = 0;
    for(int i = 0; i < prog->ndeps; i++){
        if(IS_RAR(deps[i]->type))
            continue;
        if(!depcst[i]){
            depcst[i] = get_permutability_constraints_each_dep(deps[i], prog);
            total_rows += depcst[i]->nrows;
        }
    }

    total = pluto_constraints_alloc(total_rows, CST_WIDTH);
    total->nrows = 0;
    total->ncols = CST_WIDTH;
    for(int i = 0; i < prog->ndeps; i++){
        if(IS_RAR(dep->type)){
            continue;
        }
        if(dep_is_satisfied(dep)) continue;

        pluto_constraints_add(total, depcst[i]);
        pluto_constraints_simplify(total);
    }
    return total;
}

static PlutoConstraints *refine_dep_constraints(PlutoConstraints *cst, int id, const PlutoProg *prog){
    PlutoConstraints *rt = pluto_constraints_alloc(REFINED_CST_WIDTH, cst->nrows);
    rt->nrows = cst->nrows;
    rt->ncols = REFINED_CST_WIDTH;

    for(int i = 0; i < rt->nrows; i++)
        for(int j = 0; j < rt->ncols; j++)
            rt->val[i][j] = 0;

    int offset = id*(prog->npar+1);
    for(int i = 0; i < rt->nrows; i++){
        for(int j = 0; j < prog->npar+1; j++)
            rt->val[i][j + offset] = cst->val[i][j];
        for(int j = prog->npar+1; j < rt->ncols; j++)
            rt->val[i][j] = cst->val[i][j];
    }
    return rt;
}

static void get_refined _permutablity_constraints(const PlutoProg *prog){
    
}