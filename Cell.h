#pragma once

class Peice;

class Cell
{
public:

	Cell(Peice*, int, int);

	bool isempty();

	void draw(bool = false);

	Peice* getPeice();


	void* getImptr();
	void* getImptr_();
	void* getImptrP();
	void* getImptrP_();


	void setPeice(Peice* const);

	bool getHighlighted();

	void setHighlighted(bool);

	void highlight();

	void unhighlight();

	int getx();

	int gety();

	void setimptr(void*);
	void setimptr_(void*);

	~Cell();

protected:
	int x{}, y{};

	int l{}, h{};
	
	int color{};

	bool highlighted{ false };

	Peice* pptr{nullptr};

	void* imptr;
	void* imptr_;
};

