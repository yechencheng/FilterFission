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
class source extends Filter // opt.str:12
{
  public source(int _param_n)
  {
  }
  int n; // opt.str:12
  public void work() { // opt.str:13
    for (int i = 0; (i < n); i++) { // opt.str:15
      outputChannel.pushInt(n); // opt.str:15
    }; // opt.str:14
  }
  public void init(final int _param_n) { // opt.str:12
    n = _param_n; // opt.str:12
    setIOTypes(Void.TYPE, Integer.TYPE); // opt.str:12
    addSteadyPhase(0, 0, n, "work"); // opt.str:13
  }
}
class process extends Filter // opt.str:19
{
  public process(int _param_n)
  {
  }
  int n; // opt.str:19
  public void work() { // opt.str:20
    int[n] tmp1; // opt.str:21
    int[n] tmp2; // opt.str:22
    for (int i = 0; (i < n); i++) { // opt.str:24
      tmp1[i] = inputChannel.popInt(); // opt.str:24
    }; // opt.str:23
    for (int i = 0; (i < n); i++) { // opt.str:26
      tmp1[i]++; // opt.str:26
    }; // opt.str:25
    for (int i = 0; (i < n); i++) { // opt.str:28
      tmp2[i] = (tmp1[i] + 1); // opt.str:28
    }; // opt.str:27
    for (int i = 0; (i < n); i++) { // opt.str:30
      outputChannel.pushInt(tmp2[i]); // opt.str:30
    }; // opt.str:29
  }
  public void init(final int _param_n) { // opt.str:19
    n = _param_n; // opt.str:19
    setIOTypes(Integer.TYPE, Integer.TYPE); // opt.str:19
    addSteadyPhase(n, n, n, "work"); // opt.str:20
  }
}
class print extends Filter // opt.str:34
{
  public print()
  {
  }
  public void work() { // opt.str:35
    inputChannel.popInt(); // opt.str:36
  }
  public void init() { // opt.str:34
    setIOTypes(Integer.TYPE, Void.TYPE); // opt.str:34
    addSteadyPhase(1, 1, 0, "work"); // opt.str:35
  }
}
public class opt extends StreamItPipeline // opt.str:1
{
  public void init() { // opt.str:1
    int DEPTH = 4; // opt.str:2
    int INPUT = (1 << 20); // opt.str:3
    int G = 1024; // opt.str:4
    add(new source(INPUT)); // opt.str:6
    for (int i = 0; (i < DEPTH); i++) { // opt.str:8
      add(new process(G)); // opt.str:8
    }; // opt.str:7
    add(new print()); // opt.str:9
  }
}
