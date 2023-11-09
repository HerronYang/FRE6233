// fre_ho_lee.h - Ho-Lee interest rate model for constant futures and volatility.
#pragma once
#include <cmath>
#include <random>

namespace fre::ho_lee {

	// E[exp(N)] = exp(E[N] + Var(N)/2)
	inline double Eexp(const std::normal_distribution<double>& N)
	{
		return std::exp(N.mean() + N.sigma() * N.sigma() / 2);
	}

	// D(t) = E[D_t] = exp(-rt + sigma^2*t^3/6)
	inline double ED(double φ, double σ, double t)
	{
		return std::exp(-φ * t + σ * σ * t * t * t / 6);
	}

	// φ(t) - f(t) = sigma^2 * t^2 / 2
	inline double convexity(double σ, double t)
	{
		return σ * σ * t * t / 2;
	}

	// log D_t(u) = -r * (u - t) + sigma^2 (u - t)^3 / 6 - sigma *(u - t) * B_t
	// Return mean and standard deviation of log D_t(u).
	inline std::normal_distribution<double> logD(double φ, double σ, double t, double u)
	{
		return std::normal_distribution(-φ * (u - t) + σ * σ * pow(u - t, 3) / 6, std::sqrt(pow(σ * (u - t), 2) * t));
	}

	// φ(u) - f_t(u) = sigma^2 * (u-t)^2/2 - sigma * B_t
	// Return mean and standard deviation of φ_t(u) - f_t(u)
	inline std::normal_distribution<double> convexity(double σ, double t, double u)
	{
		return std::normal_distribution(σ * σ * (u - t) * (u - t) / 2, std::sqrt(σ * σ * t));
	}

} // namespace fre::ho_lee
