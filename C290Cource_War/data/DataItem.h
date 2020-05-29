#ifndef DATAITEM_H
#define DATAITEM_H

class Item {
public:
	// ���� ������
	int Id;     // ���������� ���
	char* Name; // �������� ��������
	Item();  // ����������� ������
	~Item(); // ���������� ������
	// ������ ������


public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	Item* ListNext;
	Item* ListPred;
	virtual Item* ListFirst();
	virtual Item* ListLast();
	virtual int ListCount();
	virtual Item* ListAdd(Item* ExistingItem);
	virtual void ListSaveToFile(const char* FileName);
	virtual void ListSaveToFileItem(FILE *FileHandle);
	virtual char* LoadFromString(char* Text);
	static Item* ListLoadFromFile(const char* FileName);
};

#endif