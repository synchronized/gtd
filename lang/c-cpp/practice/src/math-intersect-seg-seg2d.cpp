#include <math.h>
#include <iostream>

inline float vperpXZ(const float* a, const float* b) { return a[0]*b[2] - a[2]*b[0]; }

/// Performs a vector subtraction. (@p v1 - @p v2)
///  @param[out]	dest	The result vector. [(x, y, z)]
///  @param[in]		v1		The base vector. [(x, y, z)]
///  @param[in]		v2		The vector to subtract from @p v1. [(x, y, z)]
/// 执行矢量减法。 （@p v1 - @p v2）
inline void dtVsub(float* dest, const float* v1, const float* v2)
{
	dest[0] = v1[0]-v2[0];
	dest[1] = v1[1]-v2[1];
	dest[2] = v1[2]-v2[2];
}

/// 判断线段是否相交
bool dtIntersectSegSeg2D(const float* ap, const float* aq,
						 const float* bp, const float* bq,
						 float& s, float& t)
{
	float u[3], v[3], w[3];
	dtVsub(u,aq,ap);
	dtVsub(v,bq,bp);
	dtVsub(w,ap,bp); //CA
	float d = vperpXZ(u,v);
	if (fabsf(d) < 1e-6f) return false;
    auto a = vperpXZ(v,w);
    auto b = vperpXZ(u,w);
    std::cout << "d:" << d << ", a:" << a << ", b:" << b << std::endl;
	s = a / d;
	t = b / d;
	return true;
}

int main() {
    float segA[6] = {
        0.0f, 0.0f, 0.0f, //A
        5.0f, 0.0f, 5.0f, //B
    };
    float segB[6] = {
        0.0f, 0.0f, 5.0f, //C
        5.0f, 0.0f, 0.0f, //D
    };

    float s = 0.0f, t = 0.0f;
    bool isInter = dtIntersectSegSeg2D(segA, segA+3, segB, segB+3, s, t);
    std::cout << "isInter:" << isInter << std::endl;
    std::cout << "s:" << s << std::endl;
    std::cout << "t:" << t << std::endl;
    return 0;
}
