#pragma once
#include <exception>

struct EmptyCourierRoute : public std::exception
{
	const char * what () const throw ()
    {
    	return "Courier has empty route queue";
    }
};

struct BadStartingRoutePoint : public std::exception
{
	const char * what () const throw ()
    {
    	return "Courier isn't in starting point of given route";
    }
};