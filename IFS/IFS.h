#include <vector>

#include "matrix.h"
#include "image.h"

class IFS
{

public:

	// Constructor and Deconstructor ~
	IFS(): m_n(0) {}
	IFS(const char *filename) { readFile(filename); }

	~IFS() {};

	void readFile(const char *filename);
	void fractalRendering(Image &img, unsigned int pointNum, unsigned int iterTimes, const char *outputFile) const;

	void printIFS() const;

private:

	// Number of Transformations ~~
	unsigned int m_n;

	std::vector<Matrix> m_transMatrix;
	std::vector<double> m_transProbality;
};
