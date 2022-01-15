//:practice-06-06/Handle.h

class Handle{
	struct Cheshire;
	Cheshire* smile;
public:
	Handle();
	~Handle();
	int read();
	void change(int i);
};
