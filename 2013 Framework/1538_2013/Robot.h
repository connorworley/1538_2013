#include <WPILib.h>
#include <vector>

#include "PeriodicSystem.h"

class Robot : public IterativeRobot
{
private:
	std::vector<PeriodicSystem*> m_PeriodicTaskPool;
public:
	static Robot* m_SingletonInstance;
	static Robot* GetInstance();
	
	Robot();
	~Robot();
	
	void RegisterPeriodicSystem(void* systemPtr);
};
