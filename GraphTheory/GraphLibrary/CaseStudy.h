#pragma once

//int caseStudy1(string path, string labelsPath);
int caseStudy2(string path, string labelsPath);

inline unsigned int RandU(unsigned int nMin, unsigned int nMax)
{
	return nMin + (unsigned int)((double)rand() / (RAND_MAX + 1) * (nMax - nMin + 1));
}