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
class source extends Filter // original.str:12
{
  public source(int _param_n)
  {
  }
  int n; // original.str:12
  public void work() { // original.str:13
    for (int i = 0; (i < n); i++) { // original.str:15
      outputChannel.pushInt(n); // original.str:15
    }; // original.str:14
  }
  public void init(final int _param_n) { // original.str:12
    n = _param_n; // original.str:12
    setIOTypes(Void.TYPE, Integer.TYPE); // original.str:12
    addSteadyPhase(0, 0, n, "work"); // original.str:13
  }
}
class process extends Filter // original.str:19
{
  public process(int _param_n)
  {
  }
  int n; // original.str:19
  public void work() { // original.str:20
    int[n] tmp1; // original.str:21
    int[n] tmp2; // original.str:22
    for (int i = 0; (i < n); i++) { // original.str:24
      tmp1[i] = inputChannel.popInt(); // original.str:24
    }; // original.str:23
    for (int i = 0; (i < n); i++) { // original.str:26
      tmp1[i]++; // original.str:26
    }; // original.str:25
    for (int i = 0; (i < n); i++) { // original.str:28
      tmp2[i] = (tmp1[i] + 1); // original.str:28
    }; // original.str:27
    for (int i = 0; (i < n); i++) { // original.str:30
      outputChannel.pushInt(tmp2[i]); // original.str:30
    }; // original.str:29
  }
  public void init(final int _param_n) { // original.str:19
    n = _param_n; // original.str:19
    setIOTypes(Integer.TYPE, Integer.TYPE); // original.str:19
    addSteadyPhase(n, n, n, "work"); // original.str:20
  }
}
class print extends Filter // original.str:34
{
  public print()
  {
  }
  public void work() { // original.str:35
    inputChannel.popInt(); // original.str:36
  }
  public void init() { // original.str:34
    setIOTypes(Integer.TYPE, Void.TYPE); // original.str:34
    addSteadyPhase(1, 1, 0, "work"); // original.str:35
  }
}
public class original extends StreamItPipeline // original.str:1
{
  public void init() { // original.str:1
    int DEPTH = 4; // original.str:2
    int INPUT = (1 << 20); // original.str:3
    int G = INPUT; // original.str:4
    add(new source(INPUT)); // original.str:6
    for (int i = 0; (i < DEPTH); i++) { // original.str:8
      add(new process(G)); // original.str:8
    }; // original.str:7
    add(new print()); // original.str:9
  }
}
