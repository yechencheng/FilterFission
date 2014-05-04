import java.io.Serializable;
import streamit.library.*;
import streamit.library.io.*;
import streamit.misc.StreamItRandom;
class Complex extends Structure implements Serializable {
  float real;
  float imag;
}
class float2 extends Structure implements Serializable {
  float x;
  float y;
}
class float3 extends Structure implements Serializable {
  float x;
  float y;
  float z;
}
class float4 extends Structure implements Serializable {
  float x;
  float y;
  float z;
  float w;
}
class StreamItVectorLib {
  public static native float2 add2(float2 a, float2 b);
  public static native float3 add3(float3 a, float3 b);
  public static native float4 add4(float4 a, float4 b);
  public static native float2 sub2(float2 a, float2 b);
  public static native float3 sub3(float3 a, float3 b);
  public static native float4 sub4(float4 a, float4 b);
  public static native float2 mul2(float2 a, float2 b);
  public static native float3 mul3(float3 a, float3 b);
  public static native float4 mul4(float4 a, float4 b);
  public static native float2 div2(float2 a, float2 b);
  public static native float3 div3(float3 a, float3 b);
  public static native float4 div4(float4 a, float4 b);
  public static native float2 addScalar2(float2 a, float b);
  public static native float3 addScalar3(float3 a, float b);
  public static native float4 addScalar4(float4 a, float b);
  public static native float2 subScalar2(float2 a, float b);
  public static native float3 subScalar3(float3 a, float b);
  public static native float4 subScalar4(float4 a, float b);
  public static native float2 scale2(float2 a, float b);
  public static native float3 scale3(float3 a, float b);
  public static native float4 scale4(float4 a, float b);
  public static native float2 scaleInv2(float2 a, float b);
  public static native float3 scaleInv3(float3 a, float b);
  public static native float4 scaleInv4(float4 a, float b);
  public static native float sqrtDist2(float2 a, float2 b);
  public static native float sqrtDist3(float3 a, float3 b);
  public static native float sqrtDist4(float4 a, float4 b);
  public static native float dot3(float3 a, float3 b);
  public static native float3 cross3(float3 a, float3 b);
  public static native float2 max2(float2 a, float2 b);
  public static native float3 max3(float3 a, float3 b);
  public static native float2 min2(float2 a, float2 b);
  public static native float3 min3(float3 a, float3 b);
  public static native float2 neg2(float2 a);
  public static native float3 neg3(float3 a);
  public static native float4 neg4(float4 a);
  public static native float2 floor2(float2 a);
  public static native float3 floor3(float3 a);
  public static native float4 floor4(float4 a);
  public static native float2 normalize2(float2 a);
  public static native float3 normalize3(float3 a);
  public static native float4 normalize4(float4 a);
  public static native boolean greaterThan3(float3 a, float3 b);
  public static native boolean lessThan3(float3 a, float3 b);
  public static native boolean equals3(float3 a, float3 b);
}
class source extends Filter // opt.str:11
{
  public source(int _param_n)
  {
  }
  int n; // opt.str:11
  public void work() { // opt.str:12
    for (int i = 0; (i < (2 * n)); i++) { // opt.str:14
      outputChannel.pushInt(i); // opt.str:14
    }; // opt.str:13
  }
  public void init(final int _param_n) { // opt.str:11
    n = _param_n; // opt.str:11
    setIOTypes(Void.TYPE, Integer.TYPE); // opt.str:11
    addSteadyPhase(0, 0, (2 * n), "work"); // opt.str:12
  }
}
class PassF extends Filter // opt.str:18
{
  public PassF()
  {
  }
  public void work() { // opt.str:19
    outputChannel.pushInt(inputChannel.popInt()); // opt.str:20
  }
  public void init() { // opt.str:18
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:18
    addSteadyPhase(1, 1, 1, "work"); // opt.str:19
  }
}
class MySplit extends Filter // opt.str:24
{
  public MySplit(int _param_n, int _param_m)
  {
  }
  int n; // opt.str:24
  int m; // opt.str:24
  public void work() { // opt.str:25
    int[m] tmp; // opt.str:26
    for (int i = 0; (i < (n / m)); i++) { // opt.str:27
      for (int j = 0; (j < m); j++) { // opt.str:28
        tmp[j] = inputChannel.peekInt(n); // opt.str:29
        outputChannel.pushInt(inputChannel.popInt()); // opt.str:30
      }; // opt.str:28
      for (int j = 0; (j < m); j++) { // opt.str:32
        outputChannel.pushInt(tmp[j]); // opt.str:33
      }; // opt.str:32
    }; // opt.str:27
    for (int i = 0; (i < n); i++) { // opt.str:37
      inputChannel.popInt(); // opt.str:37
    }; // opt.str:36
  }
  public void init(final int _param_n, final int _param_m) { // opt.str:24
    n = _param_n; // opt.str:24
    m = _param_m; // opt.str:24
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:24
    addSteadyPhase((2 * n), (2 * n), (2 * n), "work"); // opt.str:25
  }
}
class MyJoin extends Filter // opt.str:41
{
  public MyJoin(int _param_n, int _param_m)
  {
  }
  int n; // opt.str:41
  int m; // opt.str:41
  public void work() { // opt.str:42
    int[n] tmp; // opt.str:43
    int id = 0; // opt.str:44
    for (int i = 0; (i < (n / m)); i++) { // opt.str:45
      for (int j = 0; (j < m); j++) { // opt.str:47
        outputChannel.pushInt(inputChannel.popInt()); // opt.str:47
      }; // opt.str:46
      for (int j = 0; (j < m); j++) { // opt.str:49
        tmp[id++] = inputChannel.popInt(); // opt.str:49
      }; // opt.str:48
    }; // opt.str:45
    for (int i = 0; (i < n); i++) { // opt.str:53
      outputChannel.pushInt(tmp[i]); // opt.str:53
    }; // opt.str:52
  }
  public void init(final int _param_n, final int _param_m) { // opt.str:41
    n = _param_n; // opt.str:41
    m = _param_m; // opt.str:41
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:41
    addSteadyPhase((2 * n), (2 * n), (2 * n), "work"); // opt.str:42
  }
}
class Fused_MyJoin_MySplit extends Filter // opt.str:58
{
  public Fused_MyJoin_MySplit(int _param_n1, int _param_n2, int _param_m)
  {
  }
  int n1; // opt.str:58
  int n2; // opt.str:58
  int m; // opt.str:58
  public void work() { // opt.str:59
    int id = 0; // opt.str:86
    int[n2] tmp; // opt.str:87
    for (int i = 0; (i < (n2 / (2 * n1))); i++) { // opt.str:88
      for (int j = 0; (j < (n1 / m)); j++) { // opt.str:89
        for (int k = 0; (k < m); k++) { // opt.str:91
          outputChannel.pushInt(inputChannel.popInt()); // opt.str:91
        }; // opt.str:90
        for (int k = 0; (k < m); k++) { // opt.str:93
          outputChannel.pushInt(inputChannel.peekInt(((k + (2 * n1)) - m))); // opt.str:93
        }; // opt.str:92
        for (int k = 0; (k < m); k++) { // opt.str:95
          tmp[id++] = inputChannel.popInt(); // opt.str:95
        }; // opt.str:94
      }; // opt.str:89
      for (int j = 0; (j < (n1 / m)); j++) { // opt.str:97
        for (int k = 0; (k < m); k++) { // opt.str:99
          inputChannel.popInt(); // opt.str:99
        }; // opt.str:98
        for (int k = 0; (k < m); k++) { // opt.str:101
          tmp[id++] = inputChannel.popInt(); // opt.str:101
        }; // opt.str:100
      }; // opt.str:97
    }; // opt.str:88
    id = 0; // opt.str:105
    for (int k = 0; (k < (n2 / (2 * n1))); k++) { // opt.str:106
      for (int i = 0; (i < (n1 / m)); i++) { // opt.str:107
        for (int j = 0; (j < m); j++) { // opt.str:108
          outputChannel.pushInt(tmp[id++]); // opt.str:109
        }; // opt.str:108
        id -= m; // opt.str:111
        for (int j = 0; (j < m); j++) { // opt.str:112
          outputChannel.pushInt(tmp[(id++ + n1)]); // opt.str:113
        }; // opt.str:112
      }; // opt.str:107
      id += n1; // opt.str:116
    }; // opt.str:106
  }
  public void init(final int _param_n1, final int _param_n2, final int _param_m) { // opt.str:58
    n1 = _param_n1; // opt.str:58
    n2 = _param_n2; // opt.str:58
    m = _param_m; // opt.str:58
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:58
    addSteadyPhase((2 * n2), (2 * n2), (2 * n2), "work"); // opt.str:59
  }
}
class Fused_process extends Pipeline // opt.str:122
{
  public Fused_process(int DEPTH, int n, int m)
  {
  }
  public void init(final int DEPTH, final int n, final int m) { // opt.str:122
    int nn = n; // opt.str:123
    add(new MySplit(n, m)); // opt.str:124
    add(new process1(m)); // opt.str:125
    for (int i = 0; (i < (DEPTH - 1)); i++) { // opt.str:126
      nn /= 2; // opt.str:127
      add(new Fused_MyJoin_MySplit(nn, (nn * 2), m)); // opt.str:128
      add(new process1(m)); // opt.str:129
    }; // opt.str:126
    add(new MyJoin(nn, m)); // opt.str:131
  }
}
class process extends Pipeline // opt.str:135
{
  public process(int n, int m)
  {
  }
  public void init(final int n, final int m) { // opt.str:135
    add(new MySplit(n, m)); // opt.str:144
    add(new process1(m)); // opt.str:145
    add(new MyJoin(n, m)); // opt.str:146
  }
}
class process1 extends Filter // opt.str:157
{
  public process1(int _param_n)
  {
  }
  int n; // opt.str:157
  public void work() { // opt.str:158
    int[(2 * n)] tmp1; // opt.str:159
    int[(2 * n)] tmp2; // opt.str:160
    int[(2 * n)] tmp3; // opt.str:161
    for (int i = 0; (i < (2 * n)); i++) { // opt.str:163
      tmp1[i] = inputChannel.popInt(); // opt.str:163
    }; // opt.str:162
    for (int i = 0; (i < n); i++) { // opt.str:164
      tmp2[i] = tmp1[i]; // opt.str:165
      tmp2[(i + n)] = tmp1[(i + n)]; // opt.str:166
    }; // opt.str:164
    for (int i = 0; (i < (2 * n)); i++) { // opt.str:169
      tmp3[i] = tmp2[i]; // opt.str:169
    }; // opt.str:168
    for (int i = 0; (i < (2 * n)); i++) { // opt.str:170
      outputChannel.pushInt(tmp3[i]); // opt.str:171
    }; // opt.str:170
  }
  public void init(final int _param_n) { // opt.str:157
    n = _param_n; // opt.str:157
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:157
    addSteadyPhase((2 * n), (2 * n), (2 * n), "work"); // opt.str:158
  }
}
class print extends Filter // opt.str:176
{
  public print()
  {
  }
  public void work() { // opt.str:177
    System.out.print(inputChannel.peekInt(0)); // opt.str:178
    inputChannel.popInt(); // opt.str:179
  }
  public void init() { // opt.str:176
    setIOTypes(Integer.TYPE, Void.TYPE); // opt.str:176
    addSteadyPhase(1, 1, 0, "work"); // opt.str:177
  }
}
public class opt extends StreamItPipeline // opt.str:1
{
  public void init() { // opt.str:1
    int DEPTH = 8; // opt.str:2
    int INPUT = (1 << 22); // opt.str:3
    int G = 512; // opt.str:4
    add(new source(INPUT)); // opt.str:6
    add(new Fused_process(DEPTH, INPUT, G)); // opt.str:7
    add(new print()); // opt.str:8
  }
}
