#ifndef TVREMOTECONTROLLER_GRID_H
#define TVREMOTECONTROLLER_GRID_H

class Grid {
private:
	double res;
	double minRes;
	double maxRes;
public:
	static constexpr double INIT_GRID_RES = 1.0;
	static constexpr double DEFAULT_GRID_MIN_RES = 0.2;
	static constexpr double DEFAULT_GRID_MAX_RES = 2.0;

	Grid() {
		res = INIT_GRID_RES;
		minRes = DEFAULT_GRID_MIN_RES;
		maxRes = DEFAULT_GRID_MAX_RES;
	}

	double GetRes() {
		return res;
	}

	double GetMinRes() {
		return minRes;
	}

	double GetMaxRes() {
		return maxRes;
	}

	Grid& SetGridRes(double res) {

		if (minRes <= res && res <= maxRes) {
			this->res = res;
		}

		return *this;
	}

};

#endif //TVREMOTECONTROLLER_GRID_H
