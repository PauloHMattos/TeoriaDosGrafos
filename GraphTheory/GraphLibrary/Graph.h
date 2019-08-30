#pragma once


#ifdef GRAPHLIBRARY_EXPORTS
#define GRAPHLIBRARY_API __declspec(dllexport)
#else
#define GRAPHLIBRARY_API __declspec(dllimport)
#endif


class GRAPHLIBRARY_API Graph
{

};

