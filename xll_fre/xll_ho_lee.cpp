// xll_ho_lee.cpp - Ho-Lee interest rate add-ins
#include "fre_ho_lee.h"
#include "xll_fre.h"

using namespace fre;
using namespace xll;

// !!! Implement the following add-ins !!!
// HO_LEE.ED
// HO_LEE.Convexity
// HO_LEE.LogD

// This illustrates how to return an array of doubles to Excel.
AddIn xai_ho_lee_convexity2(
	Function(XLL_FPX, "xll_ho_lee_convexity2", "HO_LEE.Convexity2")
	.Arguments({
		Arg(XLL_DOUBLE, "σ", "is the volatiltiy."),
		Arg(XLL_DOUBLE, "t", "is the forward time in years"),
		Arg(XLL_DOUBLE, "u", "is the time to futures expiration in years"),
		})
	.FunctionHelp("Return the mean and standard deviation of forward convexity of a Ho-Lee model.")
	.Category(CATEGORY)
);
_FPX* WINAPI xll_ho_lee_convexity2(double σ, double t, double u)
{
#pragma XLLEXPORT
	static xll::FPX stdev(1, 2); // 1x2 array of doubles

	try {
		std::normal_distribution<double> N = ho_lee::convexity(σ, t, u);

		stdev[0] = N.mean();
		stdev[1] = N.stddev();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // #NUM!
	}

	return stdev.get();
}

AddIn xai_ho_lee_ed(
	Function(XLL_DOUBLE, "xll_ho_lee_ed", "HO_LEE.ED")
	.Arguments({
		Arg(XLL_DOUBLE, "φ", "is the futures quote."),
		Arg(XLL_DOUBLE, "σ", "is the volatiltiy."),
		Arg(XLL_DOUBLE, "t", "is the forward time in years"),
		})
	.FunctionHelp("Return the expectation of D_t.")
	.Category(CATEGORY)
);
double WINAPI xll_ho_lee_ed(double φ, double σ, double t)
{
#pragma XLLEXPORT
	return fre::ho_lee::ED(φ, σ, t);
}

AddIn xai_ho_lee_convexity(
	Function(XLL_DOUBLE, "xll_ho_lee_convexity", "HO_LEE.Convexity")
	.Arguments({
		Arg(XLL_DOUBLE, "σ", "is the volatiltiy."),
		Arg(XLL_DOUBLE, "t", "is the forward time in years"),
		})
	.FunctionHelp("Return the convexity.")
	.Category(CATEGORY)
);
double WINAPI xll_ho_lee_convexity(double σ, double t)
{
#pragma XLLEXPORT
	return fre::ho_lee::convexity(σ, t);
}

AddIn xai_ho_lee_logD(
	Function(XLL_FPX, "xll_ho_lee_logD", "HO_LEE.LogD")
	.Arguments({
		Arg(XLL_DOUBLE, "φ", "is the futures quote."),
		Arg(XLL_DOUBLE, "σ", "is the volatiltiy."),
		Arg(XLL_DOUBLE, "t", "is the forward time in years"),
		Arg(XLL_DOUBLE, "u", "is the maturing time. ")
		})
	.FunctionHelp("Return the distribution of log D_t(u).")
	.Category(CATEGORY)
);
_FPX* WINAPI xll_ho_lee_logD(double φ, double σ, double t, double u)
{
#pragma XLLEXPORT
	static xll::FPX stdev(1, 2); // 1x2 array of doubles

	try {
		std::normal_distribution<double> N = ho_lee::logD(φ, σ, t, u);

		stdev[0] = N.mean();
		stdev[1] = N.stddev();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0; // #NUM!
	}

	return stdev.get();
}
