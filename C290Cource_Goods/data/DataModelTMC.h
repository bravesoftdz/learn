#ifndef DATAMODELTMC_H
#define DATAMODELTMC_H

class TMC {
public: // ���� ������
	int Id;        // ��� ������
	char* Name;    // ������������
	char* Article; // ������� ������
	char* Measure; // ������� ���������
	double Price;  // ����
	double Quant;  // ���-�� �� ������
	double Limit;  // ���������� ���-�� �� ������
public: // ������ ������
	TMC();
	~TMC();
	virtual void Print();
	virtual void Save(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	virtual void GenTest(); // ��������� �������� ������ ��� �������
public: // ���� � ������ ��� ������ � ���.�������� ��� � ��������� ����������� ������
	TMC* ListNext;
	TMC* ListPred;
	virtual TMC* ListFirst();
	virtual TMC* ListLast();
	virtual int ListCount();
	virtual TMC* ListAdd(TMC* ExistingItem);
	virtual void ListPrint();
	void ListSave(const char* FileName);
};

#endif