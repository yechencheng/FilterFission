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
class source extends Filter // original.str:17
{
  public source(int _param_n)
  {
  }
  int n; // original.str:17
  public void work() { // original.str:18
    for (int i = 0; (i < (2 * n)); i++) { // original.str:20
      outputChannel.pushInt(i); // original.str:20
    }; // original.str:19
  }
  public void init(final int _param_n) { // original.str:17
    n = _param_n; // original.str:17
    setIOTypes(Void.TYPE, Integer.TYPE); // original.str:17
    addSteadyPhase(0, 0, (2 * n), "work"); // original.str:18
  }
}
class PassF extends Filter // original.str:24
{
  public PassF()
  {
  }
  public void work() { // original.str:25
    outputChannel.pushInt(inputChannel.popInt()); // original.str:26
  }
  public void init() { // original.str:24
    setIOTypes(Integer.TYPE, Integer.TYPE); // original.str:24
    addSteadyPhase(1, 1, 1, "work"); // original.str:25
  }
}
class process extends Pipeline // original.str:30
{
  public process(int n, int m)
  {
  }
  public void init(final int n, final int m) { // original.str:30
    add(new AnonFilter_a0(m, n)); // original.str:31
    add(new process1(m)); // original.str:37
    add(new AnonFilter_a1(m, n)); // original.str:38
  }
}
class process1 extends Filter // original.str:46
{
  public process1(int _param_n)
  {
  }
  int n; // original.str:46
  public void work() { // original.str:47
    int[(2 * n)] tmp1; // original.str:48
    int[(2 * n)] tmp2; // original.str:49
    int[(2 * n)] tmp3; // original.str:50
    for (int i = 0; (i < (2 * n)); i++) { // original.str:52
      tmp1[i] = inputChannel.popInt(); // original.str:52
    }; // original.str:51
    for (int i = 0; (i < n); i++) { // original.str:53
      tmp2[i] = tmp1[i]; // original.str:54
      tmp2[(i + n)] = tmp1[(i + n)]; // original.str:55
    }; // original.str:53
    for (int i = 0; (i < (2 * n)); i++) { // original.str:60
      tmp3[i] = tmp2[i]; // original.str:60
    }; // original.str:59
    for (int i = 0; (i < (2 * n)); i++) { // original.str:61
      outputChannel.pushInt(tmp3[i]); // original.str:62
    }; // original.str:61
  }
  public void init(final int _param_n) { // original.str:46
    n = _param_n; // original.str:46
    setIOTypes(Integer.TYPE, Integer.TYPE); // original.str:46
    addSteadyPhase((2 * n), (2 * n), (2 * n), "work"); // original.str:47
  }
}
class print extends Filter // original.str:68
{
  public print()
  {
  }
  public void work() { // original.str:69
    System.out.print(inputChannel.peekInt(0)); // original.str:70
    inputChannel.popInt(); // original.str:71
  }
  public void init() { // original.str:68
    setIOTypes(Integer.TYPE, Void.TYPE); // original.str:68
    addSteadyPhase(1, 1, 0, "work"); // original.str:69
  }
}
class AnonFilter_a0 extends SplitJoin // original.str:31
{
  public AnonFilter_a0(int m, int n)
  {
  }
  public void init(final int m, final int n) { // original.str:31
    setSplitter(WEIGHTED_ROUND_ROBIN(n, n)); // original.str:32
    add(new PassF()); // original.str:33
    add(new PassF()); // original.str:34
    setJoiner(WEIGHTED_ROUND_ROBIN(m, m)); // original.str:35
  }
}
class AnonFilter_a1 extends SplitJoin // original.str:38
{
  public AnonFilter_a1(int m, int n)
  {
  }
  public void init(final int m, final int n) { // original.str:38
    setSplitter(WEIGHTED_ROUND_ROBIN(m, m)); // original.str:39
    add(new PassF()); // original.str:40
    add(new PassF()); // original.str:41
    setJoiner(WEIGHTED_ROUND_ROBIN(n, n)); // original.str:42
  }
}
public class original extends StreamItPipeline // original.str:1
{
  public void init() { // original.str:1
    int DEPTH = 8; // original.str:2
    int INPUT = (1 << 22); // original.str:3
    int G = INPUT; // original.str:4
    add(new source(INPUT)); // original.str:6
    int data = INPUT; // original.str:8
    for (int i = 0; (i < DEPTH); i++) { // original.str:9
      add(new process1(data)); // original.str:10
      data /= 2; // original.str:11
    }; // original.str:9
    add(new print()); // original.str:14
  }
}
