#ifndef TEST_H_
#define TEST_H_

class Test {
public:
	Test();
	Test(const Test &other);
	Test operator=(const Test &test);
	bool operator>(const Test &other);
	operator float();
	Test operator=(float);
	virtual ~Test();
};

#endif /* TEST_H_ */
