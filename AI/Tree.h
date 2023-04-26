#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
namespace Jeff
{
#define NF "Not Found"
#define VALUETYPE double
	class Data
	{
		string Field;
		VALUETYPE Value;
	public:
		Data() :Value(0)
		{}
		Data(string inField) :Field(inField), Value(0)
		{}
		constexpr Data(string inField, VALUETYPE inValue) : Field(inField), Value(inValue)
		{}
		Data(const Data& Obj)
		{
			this->Value = Obj.Value;
			this->Field = Obj.Field;
		}
		VALUETYPE value_Get()
		{
			return Value;
		}
		string field_Get()
		{
			return Field;
		}
		Data this_Get()
		{
			return *this;
		}
		void value_Change(VALUETYPE newValue)
		{
			Value = newValue;
		}
		void field_Change(string newField)
		{
			Field = newField;
		}
		bool field_Compare(string inField)
		{
			return this->Field == inField;
		}
		bool operator==(Data& Obj)
		{
			return Obj.Field == this->Field && Obj.Value == this->Value;
		}
		friend istream& operator>>(istream& Result, Data In)
		{
			Result >> In.Field >> In.Value;
			return Result;
		}
		friend ostream& operator<<(ostream& Result, Data In)
		{
			Result << In.Field << ":" << In.Value;
			return Result;
		}
		VALUETYPE& operator=(VALUETYPE inData)
		{
			this->Value = inData;
			return this->Value;
		}
		string& operator=(string Field)
		{
			this->Field = Field;
			return this->Field;
		}
	};
	//��ʾ�ڶ���Data����Field��λ��δƥ�䵽����Ҫ���ֵ����Ϊ��������ֵʹ��
	Data NF_data(NF);
}
namespace Jeff
{
	/*
	* in ���������ϲ㴫��
	* new���������ϲ㴫���һ��ڱ�������½�Ӱ��ı���
	*/
	class Node
	{
	public:
		////////////////////////////////////////////
		using NodeNext = vector<Node*>;
		using Value = vector<Data>;
		///////////////////////////////////////////
	private:
		string ID;
		string Name;
		Node* Father;
		Value Values;//���ݿռ�
		NodeNext Next;//ָ��ռ䣬��ʾ��һ���ڵ�
		//����vector���ڴ�����ʹNode�����Fatherָ��ʧЧ������ʹ��ָ��ռ�ķ�ʽ���ӡ�
		bool Visible;
		Node* NF_node = NULL;

		ostream& OutPut(ostream& Out, Node* Last = NULL, int Layer = 1)
		{
			if (Last == NULL)
			{
				Last = this;
				Out << "0: " << Last->Name << ":";
				for (auto& Temp : Last->Values)
					Out << "-" << Temp << "\t";
				Out << endl;
			}
			NodeNext TempNext = Last->Next;
			for (auto& Temp : TempNext)
			{
				for (int n = 0; n != Layer; n++)
					Out << '\t';
				Out << Layer << ": " << Temp->Name << ":";
				for (auto& TempValue : Last->Values)
					Out << "-" << TempValue << "\t";
				Out << endl;
				if (TempNext.size() != 0)
					OutPut(Out, Temp, Layer + 1);
			}
			return Out;
		}
	public:
		Node() :Father(NULL), Visible(true)
		{}
		Node(string stationName, Node* inFather = NULL, bool inVisible = true) //���ڿ��ٲ���������ӿ�
			:Name(stationName), Father(inFather), Visible(inVisible)
		{}
		Node(string stationName, Data newValue, Node* inFather = NULL, bool inVisible = true)//ȫ�����½�Node
			:Name(stationName), Father(inFather), Visible(inVisible)
		{
			Values.push_back(newValue);
		}
		Node(Node& inNode)
			:Name(inNode.Name), Father(inNode.Father),
			Values(inNode.Values), Next(inNode.Next), Visible(inNode.Visible), ID(inNode.ID)
		{}
		/*
		* ���ݲ�����Ϊ��������
		* ���ݲ��� (value)
		* �ڵ��ϵ���� (node)
		* ���Ʋ��� (name)
		*/
		//name
		void name_Change(string newName)
		{
			this->Name = newName;
		}
		string name_Get()
		{
			return this->Name;
		}
		bool name_Compare(string inName)
		{
			if (this != NULL)
				return (this->Name == inName);
			else
				return false;
		}
		/////////////////////////////////////////////////////////////

		//value
		Data& value_Add(string newField)
		{
			this->Values.push_back(newField);
		}
		Data& value_Locate(string inField)
		{
			for (auto& Waiting : Values)
			{
				if (Waiting.field_Compare(inField))
					return Waiting;
			}
			return NF_data;
		}
		VALUETYPE value_Get(string inField)
		{
			return value_Locate(inField).value_Get();
		}
		void value_FieldChange(Data goal, string inField)
		{
			goal.field_Change(inField);
		}
		string id_Get()
		{
			return ID;
		}
		//�Ӻţ�����ֶΣ����Ұ����豸���
		//bool���������ɹ�/ʧ��
		/*bool id_Generate(int* Requirement)
		{
			const int size = 4;
			if (_msize(Requirement) / sizeof(int) != size)
				return false;
			else
			{
				for (int n = 0;n!= size;n++)
					ID += Requirement[n]+48;
			}
			return true;
		}*/
		void visible_Change()
		{
			this->Visible = !this->Visible;
		}
		bool visible_Get()
		{
			return this->Visible;
		}
		////////////////////////////////////////////////////////////

		//node
		//Fatherָ����ز���
		void father_Change(Node* inFather)
		{
			this->Father = inFather;
		}
		Node* father_Get()
		{
			return this->Father;
		}
		//////////////////////////////////////////////////
		//��ȡָ��ռ������ֵ
		int node_Index(string stationName)
		{
			for (int n = 0; n != Next.size(); n++)
			{
				if (Next[n]->Name == stationName)
					return n;
			}
			return -1;
		}
		//��ȡָ��ռ�ľ������
		Node& node_Locate(string stationName, Node* Last = NULL)
		{
			if (this->Name == stationName)
				return *this;
			for (auto& tempNext : Next)
				if (tempNext->Name == stationName)
					return *tempNext;
			return *NF_node;
		}
		//�½�ͬ��ڵ�
		Node& node_Add(Node newNode)
		{
			Node* tempNew = new Node(newNode);
			tempNew->father_Change(this);
			this->Next.push_back(tempNew);
		}
		Node& node_Add(string newStationName)
		{
			Node* tempNew = new Node(newStationName, this);
			this->Next.push_back(tempNew);
			return *Next[Next.size() - 1];
		}
		//�½���һ��ڵ�
		Node& node_AddNext(string goalNodeName, Node newNode)
		{
			auto& Temp = node_Locate(goalNodeName);
			if (!Temp.name_Compare(NF))
				return Temp.node_Add(newNode);
			else
				return *NF_node;
		}
		int node_NextSize()
		{
			return this->Next.size();
		}
		Node& node_AddNext(string goalNodeName, string newNode)
		{
			Node NF_node(NF);
			auto& Temp = node_Locate(goalNodeName);
			if (!Temp.name_Compare(NF))
				Temp.node_Add(newNode);
			else
				return NF_node;
		}
		NodeNext node_GetAll()
		{
			return this->Next;
		}
		//ɾ���ڵ�
		Node& node_Del(string stationName)
		{
			int tempIndex = node_Index(stationName);
			delete Next[tempIndex];
			Next.erase(Next.begin() + tempIndex);
		}
		////////////////////////////////////////////////////////////

		//operator
		//���������
		Node& operator=(Node inNode)
		{
			this->Father = inNode.Father;
			this->Name = inNode.Name;
			this->Next = inNode.Next;
			this->Values = inNode.Values;
			this->Visible = inNode.Visible;
			return *this;
		}
		bool operator ==(string goalName)
		{
			return this->Name == goalName;
		}
		bool operator !=(string goalName)
		{
			return this->Name != goalName;
		}
		//�����ڵ㷽��
		Node& operator+=(Node newStation)
		{
			return this->node_Add(newStation);
		}
		Node& operator+=(string newStationName)
		{
			return this->node_Add(newStationName);
		}
		Node& operator -=(string stationName)
		{
			return this->node_Del(stationName);
		}
		Node& operator>>(Node Next)
		{
			return this->node_Add(Next);
		}
		Node& operator>>(string Next)
		{
			return this->node_Add(Next);
		}
		friend ostream& operator<<(ostream& Out, Node& Obj)
		{
			return Obj.OutPut(Out);
		}
		//���ٷ������������Data��������в���
		Data& operator[](string FieldName)
		{
			Data& Result = value_Locate(FieldName);
			if (!Result.field_Compare(NF))
				return Result;
			else
			{
				Values.push_back(FieldName);
				return Values[Values.size() - 1];
			}
		}
		////////////////////////////////////////////////////////////
		~Node()
		{
			Father = NULL;
			Values.clear();
			for (auto& Nodes : Next)//���Next�е��ڴ�ռ�
				delete Nodes;
			Next.clear();//���ָ��ռ�
		}

	};
	Node NF_node(NF);
}
namespace Jeff
{
	class Tree
	{
		string treeName;
		Node Root;//���ڵ�
		Node* Current;
	private:
	public:
		Tree() :Current(NULL)
		{}
		Tree(string newTreeName) :treeName(newTreeName), Current(NULL)
		{}
		Tree(Node newRoot, string newTreeName)
			:Root(newRoot), treeName(newTreeName), Current(&Root)
		{
		}
		string tree_GetName()
		{
			return this->treeName;
		}
		bool tree_NameCompare(string inName)
		{
			return this->treeName == inName;
		}
		void tree_ChangeName(string Name)
		{
			this->treeName = Name;
		}
		Node& tree_Locate(string goalName, Node* Temp = NULL)
		{
			if (Temp == NULL)
				Temp = &Root;
			Node* Result = &Temp->node_Locate(goalName);
			if (Result != NULL && !(Result->name_Compare(NF)))
				return *(Current = Result);
			else
			{
				Node::NodeNext TempNext = Temp->node_GetAll();
				for (auto& Next : TempNext)
				{
					Result = &tree_Locate(goalName, Next);
					if (!Result->name_Compare(NF))
						return *(Current = Result);
				}
				return NF_node;
			}
		}
		/*	if (!Current->name_Compare( stationName))
			{
				Node* Result;
				if (Current != &Root)
				{
					Result = locate_FromHead(stationName, &Root);
					if (Result != NULL)
						return *Result;
				}
				Result = locate_FromCurrent(stationName, Current);
				if (Result != NULL)
					return *Result;
				else
					return NF_node;
			}
			else
				return *Current;
		*/
		ostream& tree_OutPut(ostream& Out, Node* Last = NULL)
		{
			static int Depth = 1;
			if (Last == NULL)
			{
				Last = &Root;
				Out << this->treeName << ":" << "\v *" << this->Root;
			}
			else
				Depth++;
			for (auto& Temp : Last->node_GetAll())
			{
				Out << "\v";
				for (int n = 0; n != Depth; Out << "\t", n++);
				for (int n = 0; n != Depth + 1; Out << "*", n++);
				Out << *Temp;
				if (Temp->node_NextSize() != 0)
					tree_OutPut(Out, Temp);
			}
			return Out;
		}
		Node& operator[](string stationName)
		{
			if (Current != NULL)
			{
				Node* Result = &tree_Locate(stationName);
				if (Result->name_Compare(NF))
					return Current->node_Add(stationName);
				else
					return *Result;
			}
			else
			{
				Root = stationName;
				Current = &Root;
				return Root;
			}
		}
		bool operator==(string inName)
		{
			return this->treeName == inName;
		}
		bool operator!=(string inName)
		{
			return this->treeName != inName;
		}
		friend ostream& operator << (ostream& Out, Tree& Obj)
		{
			Out << Obj.Root;
			return Out;
		}
	};
	Tree NF_tree(NF);
}
#endif