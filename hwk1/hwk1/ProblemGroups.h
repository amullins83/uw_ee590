#pragma once
#include <map>

////////////// PROBLEMS
class Problem
{
public:
	Problem(float(*prob)(), const std::string& annotation) : problem_(prob), problem_annotation_(annotation) {}
	virtual float operator()()
	{
		return problem_();
	};

	std::string Annotation() { return problem_annotation_; }
private:
	std::string problem_annotation_;
	float(*problem_)();
};

////////////// Groups
class ProblemGroup
{
public:
	ProblemGroup(int groupNum, const std::string& annotation) : problem_group_num_(groupNum), problem_group_annotation_(annotation) {}
	float operator()(int problem);

	std::map<int, Problem*> problems_;
	int GroupNum() { return problem_group_num_; }

	std::string Annotation() { return problem_group_annotation_; }
protected:
	std::string problem_group_annotation_;
	int problem_group_num_;
};


////////////////// MANAGER
class GroupManager
{
public:
	GroupManager(const std::string& name);
	~GroupManager();
	void PrintGroupMenu();
	float Run();
	virtual std::string ProblemGroupName() { return std::string(); }
	virtual std::string ProblemName() { return std::string(); }

protected:
	std::string GroupName;
	std::map<int, ProblemGroup*> groups_;
};