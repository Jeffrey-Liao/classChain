#pragma once
#ifndef CHAIN_H
#define CHAIN_H
#include"Node.h"
#include "Auto.h"
#define NAMEAUTO "class Auto"
#define VALIDTYPES(TypeName) (TypeName == NAMEINT||TypeName == NAMEFLOAT||TypeName == NAMEDOUBLE|| TypeName == NAMELONG||TypeName == NAMESTRING||TypeName == NAMEAUTO)
namespace Manipulate
{
	enum class ChainErrorFlags
	{
		CHAIN_EMPTY,
		FAIL,
		INDEX_OVERFLOW,
		INDEX_ZERO,
		INDEX_LESSTHANZERO,
		INDEX_NULL,
		ARRAY_EMPTY,
		ARRAY_OVERFLOW
	};
	class ChainErrorProcess
	{
		std::string Error;
	public:
		ChainErrorProcess(ChainErrorFlags Flag, char Language = 'C')
		{
			if (Language == 'C' || Language == 'c')
			{
				if (Flag == ChainErrorFlags::CHAIN_EMPTY)
					Error = "链表被摧毁或链表尚未初始化！";
				else if (Flag == ChainErrorFlags::FAIL)
					Error = "出现了意外的操作失败！";
				else if (Flag == ChainErrorFlags::INDEX_OVERFLOW)
					Error = "接收到的参数远大于链表的长度，访问严重超限！";
				else if (Flag == ChainErrorFlags::INDEX_ZERO)
					Error = "此处参数不能为0";
				else if (Flag == ChainErrorFlags::INDEX_LESSTHANZERO)
					Error = "参数不能为负数";
				else if (Flag == ChainErrorFlags::INDEX_NULL)
					Error = "接收到空指针，此处不可出现空指针！";
				else if (Flag == ChainErrorFlags::ARRAY_EMPTY)
					Error = "传入的用于初始化的数组为空指针！";
				else if (Flag == ChainErrorFlags::ARRAY_OVERFLOW)
					Error = "数组索引值大于数组长度，访问超限！";
			}
			else if (Language == 'E' || Language == 'e')
			{

			}
			else
				"Selected language is not support by current version.";
			throw(Error);
		}
	};
	template<class TYPE>
	class ChainNode :public Node<TYPE>
	{
	protected:
		ChainNode* Previous;
		ChainNode* Next;
	public:
		ChainNode() :Next(NULL), Previous(NULL), Node<TYPE>()
		{
		}
		constexpr ChainNode(TYPE Data) : Previous(NULL), Next(NULL), Node<TYPE>(Data)
		{}
		constexpr ChainNode( ChainNode* Father, ChainNode* Son, TYPE Data) : Previous(Father), Next(Son), Node<TYPE>(Data)
		{
			if (Father != NULL)
				Father->Next = this;
			if (Next != NULL)
				Next->Previous = this;
		}
		constexpr ChainNode(ChainNode* Father, ChainNode* Son) :Previous(Father), Next(Son), Node<TYPE>()
		{
			if (Father != NULL)
				Father->Next = this;
			if (Next != NULL)
				Next->Previous = this;
		}
		inline void link(ChainNode* Father, ChainNode* Son);
		void connect(ChainNode* Father, ChainNode* Son);
		ChainNode* get_Next()
		{
			return this->Next;
		}
		ChainNode* get_Previous()
		{
			return this->Previous;
		}
		ChainNode* operator =(ChainNode& Obj)
		{
			this->m_data = Obj.m_data;
			return this;
		}
		ChainNode* operator= (TYPE Indata)
		{
			this->m_data = Indata;
			return this;
		}
		~ChainNode()
		{
			if (this->Previous != NULL)
				this->Previous->Next = this->Next;//如果当前节点非首，将本节点的前驱和后继链接
			if (this->Next != NULL)
				this->Next->Previous = this->Previous;//如果当前节点非尾，将本节点的前驱和后继链接
		}
	};
	//////////////////////////////////////////////////////////////////
	template<class TYPE>
	class Chain
	{
	private:
		ChainNode<TYPE>* Head;
		ChainNode<TYPE>* End;
		TYPE* Array;
		int m_size;
	public:
		Chain() :m_size(0), Head(NULL), End(NULL), Array(NULL)
		{
		}
		ChainNode<TYPE>* get_Head();//返回头结点
		ChainNode<TYPE>* get_End();
		int Size()const;
		bool Empty() const;
		ChainNode<TYPE>* Locate(const int Pos) const;
		void Append(const TYPE inData);
		void Append(TYPE* inArray, const int size);
		ChainNode<TYPE>* Allocate(const int size, TYPE Default);
		ChainNode<TYPE>* Allocate(const int size);
		bool Delete(ChainNode<TYPE>* Element = this->End);
		bool Delete(const int Pos = m_size);
		bool Destroy();
		ChainNode<TYPE>* Insert(const TYPE InsertData, const int Pos = m_size);
		ChainNode<TYPE>* Insert(const int Pos, TYPE* InsertData, const int dataSize);
		const TYPE Get(int Pos = -1) const;
		bool Change(ChainNode<TYPE>* Pos, const TYPE inData);
		bool Change(const int Location, const TYPE InData);
		ChainNode<TYPE>* Move(ChainNode<TYPE>* Pos, const int Destination);
		ChainNode<TYPE>* Copy(const int Pos, const int Destination);
		const TYPE* Arraylize();
		const TYPE& operator [](int Index) const;
		void operator =(const Chain& Obj);
		Chain<TYPE>& operator+=(const Chain& Obj);
		Chain<TYPE>& operator+=(const TYPE& Obj);
		friend ostream& operator<<(ostream& Obj, Chain<TYPE> Data)
		{
			for (int n = 0; n != Data.Size(); n++)
				Obj << Data[n]<<" ";
			return Obj;
		}
		///////////////////////////////////////////////////////////////////////
		//algorithms
		//////////////////////////////////////////////////////////////////////
		ChainNode<TYPE>* Find(const TYPE Infor);
		void Sort();
		~Chain()
		{
			Destroy();
		}
	};
	//////////////////////////////////////////////////////////////////////////////////
	// DEF
	// ///////////////////////////////////////////////////////////////////////////////////////////
	// 
	/////////////////////////////////////////////////////////////////////////////////////////////
		//ChainNode
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class TYPE>
	inline void ChainNode<TYPE>::link(ChainNode<TYPE>* Father, ChainNode<TYPE>* Son)
	{
		if (Father != NULL)
			Father->Next = Son;
		if (Son != NULL)
			Son->Previous = Father;
	}//链接该节点的子父节点
	template <class TYPE>
	void ChainNode<TYPE>::connect(ChainNode<TYPE>* Father, ChainNode<TYPE>* Son)
	{
		if (Father != NULL)
			Father->Next = this;
		this->Previous = Father;
		if (Son != NULL)
			Son->Previous = this;
		this->Next = Son;
	}//将该节点链接到子父节点
	/////////////////////////////////////////////////////////////////////////////////////////////
	//Chain
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::get_Head()
	{
		return Head;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::get_End()//返回尾结点
	{
		return End;
	}
	template<class TYPE>
	int Chain<TYPE>::Size() const
	{
		return m_size;
	}
	template<class TYPE>
	bool Chain<TYPE>::Empty() const
	{
		if (m_size != 0)
			return false;
		else
			return true;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Locate(const int Pos) const
	{
		if (!Empty() && Pos <= m_size - 1)
		{
			static ChainNode<TYPE>* Temp = this->Head;
			static int LastPos;
			ChainNode<TYPE>* FromHead = this->Head, * FromEnd = this->End;
			for (int n = LastPos, j = 0; LastPos != Pos; LastPos = n)
			{
				if (j == Pos)
				{
					Temp = FromHead, LastPos = j;
					break;
				}
				else if (m_size - j == Pos)
				{
					Temp = FromEnd, LastPos = j;
					break;
				}
				if (n > Pos && (LastPos - Pos) < (m_size / 2))
					n--, Temp = Temp->get_Previous();
				else if (n < Pos && (LastPos - Pos) < (m_size / 2))
					n++, Temp = Temp->get_Next();
				else
				{
					FromHead = FromHead->get_Next(), FromEnd = FromEnd->get_Previous();
					j++;
				}
			}
			return Temp;
		}
		else if (Pos >= m_size - 1)
			new ChainErrorProcess(ChainErrorFlags::INDEX_OVERFLOW);
		else if (Pos < 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_LESSTHANZERO);
		else
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY, 'C');
		return NULL;
	}
	template<class TYPE>
	void Chain<TYPE>::Append(TYPE inData)
	{

		if (Head == NULL)
			Head = End = new ChainNode<TYPE>(inData);
		else
			End = new ChainNode<TYPE>(End, NULL, inData);
		this->m_size++;

	}
	template<class TYPE>
	void Chain<TYPE>::Append(TYPE* inArray, int size)
	{
		if (inArray != NULL && size >= 0)
			for (int n = 0; n != size; n++) this->Append(inArray[n]);
		else if (size == 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_ZERO);
		else if (size < 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_LESSTHANZERO);
		else if (inArray == NULL)
			new ChainErrorProcess(ChainErrorFlags::ARRAY_EMPTY, 'C');
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Allocate(int size, TYPE Default)
	{
		if (size > 0)
		{
			this->m_size += size;
			ChainNode<TYPE>* Place = NULL;
			for (int n = 0; n != size; n++, End = Place)
			{
				Place = new ChainNode<TYPE>(End, NULL, Default);
				if (this->Head == NULL)
					this->Head = Place;
			}
			return Place;
		}
		else if (size == 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_ZERO, 'C');
		else
			new ChainErrorProcess(ChainErrorFlags::INDEX_LESSTHANZERO, 'C');
		return NULL;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Allocate(const int size)
	{
		if (size > 0)
		{
			this->m_size += size;
			ChainNode<TYPE>* Place = NULL;
			for (int n = 0; n != size; n++, End = Place)
			{
				Place = new ChainNode<TYPE>(End, NULL);
				if (Head == NULL)
					Head = Place;
			}
			return Place;
		}
		else if (size == 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_ZERO, 'C');
		else
			new ChainErrorProcess(ChainErrorFlags::INDEX_LESSTHANZERO, 'C');
		return NULL;
	}
	template<class TYPE>
	bool Chain<TYPE>::Delete(ChainNode<TYPE>* Element)
	{
		if (!Empty())
		{
			m_size--;
			if (Element != NULL)
				delete Element;
			else
				new ChainErrorProcess(ChainErrorFlags::INDEX_NULL);
		}
		else
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY, 'C');
		return true;
	}
	template<class TYPE>
	bool Chain<TYPE>::Delete(int Pos)
	{
		if (Pos == m_size)
			m_size--, End = End->get_Previous(), delete End->get_Next();
		else
			Delete(Locate(Pos));
		return true;
	}
	template<class TYPE>
	bool Chain<TYPE>::Destroy()
	{
		if (m_size != 0 || Head != NULL)
		{
			m_size = 0;
			for (; End != Head;)
			{
				End = End->get_Previous();
				delete End->get_Next();
			}
			delete Head;
			Head = NULL;
			delete Array;
			Array = NULL;
			End = NULL;
		}
		else
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY);
		return true;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Insert(const TYPE InsertData, const int Pos)
	{
		if (Pos <= m_size && Pos >= 0 && !Empty())
		{
			if (Pos == m_size)
			{
				this->Append(InsertData);
				return End;
			}
			else
			{
				ChainNode<TYPE>* Temp = NULL;
				Temp = Locate(Pos);
				m_size++;
				if (Temp == Head)
				{
					Head = new ChainNode<TYPE>(NULL, Head, InsertData);
					return Head;
				}
				else
				{
					Temp = new ChainNode<TYPE>(Temp->get_Previous(), Temp, InsertData);
					return Temp;
				}
			}
		}
		else if (Pos == 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_ZERO);
		else if (Pos < 0)
			new ChainErrorProcess(ChainErrorFlags::INDEX_LESSTHANZERO);
		else
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY);
		return NULL;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Insert(const int Pos, TYPE* InsertData, const int dataSize)
	{
		if (m_size >= 0)
		{
			if (Head == NULL)
				Append(InsertData, dataSize);
			else
			{
				this->m_size = this->m_size + dataSize;
				ChainNode<TYPE>* Terminal = Locate(Pos), * New = new ChainNode<TYPE>(Terminal->get_Previous(), Terminal);
				if (Pos == 0)
					this->Head = New;
				for (int n = 0;; n++, New = new ChainNode<TYPE>(New, Terminal))
				{
					New->set_Data(InsertData[n]);
					if (n + 1 == dataSize)
						break;
				}
				return Terminal;
			}
		}
		else if (Pos == m_size)
			Append(InsertData, dataSize);
		else if (Empty())
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY);
		return NULL;
	}
	template<class TYPE>
	const TYPE Chain<TYPE>::Get(const int Pos) const
	{
		if (Pos == -1)
			return this->End->data_Read();
		else
			return Locate(Pos)->data_Read();
	}
	template<class TYPE>
	bool Chain<TYPE>::Change(ChainNode<TYPE>* Pos, TYPE inData)
	{
		if (Pos != NULL)
			Pos->set_Data(inData);
		else
			new ChainErrorProcess(ChainErrorFlags::INDEX_NULL);
		return true;
	}
	template<class TYPE>
	bool Chain<TYPE>::Change(int Location, TYPE InData)
	{
		Change(Locate(Location), InData);
		return true;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Move(ChainNode<TYPE>* Pos, int Destination)
	{
		Pos->link(Pos->get_Previous(), Pos->get_Next());
		Pos->connect(Locate(Destination)->get_Previous(), Locate(Destination));
		return Pos;
	}
	template<class TYPE>
	ChainNode<TYPE>* Chain<TYPE>::Copy(int Pos, int Destination)
	{
		ChainNode<TYPE>* Temp = Locate(Destination);
		Temp->set_Data(Locate(Pos)->data_Read());
		return Temp;
	}
	template<class TYPE>
	const TYPE* Chain<TYPE>::Arraylize()
	{
		if (!Empty())
		{
			static int oldSize = m_size;
			if (Array == NULL)
			{
				Array = new TYPE[m_size];
				ChainNode<TYPE>* Pointer = Head;
				for (int n = 0; Pointer != NULL && n != m_size; n++, Pointer = Pointer->get_Next())
					Array[n] = Pointer->data_Read();
				return Array;
			}
			else if (oldSize != m_size)
			{
				TYPE* Temp = new TYPE[m_size];
				ChainNode<TYPE>* Pointer = Locate(oldSize);
				for (int n = 0; n != m_size; n++)
				{
					if (n < oldSize)
						Temp[n] = Array[n];
					else
						Temp[n] = Pointer->data_Read(), Pointer = Pointer->get_Next();
				}
				oldSize = m_size;
				delete[] Array;
				Array = Temp;
				return Array;
			}
		}
		else
			new ChainErrorProcess(ChainErrorFlags::CHAIN_EMPTY);
		return NULL;
	}
	template<class TYPE>
	void Chain<TYPE>::operator= (const Chain& Obj)
	{
		ChainNode<TYPE>* Temp = this->Head, * TempObj = Obj.Head;//本链和作用链
		if (Temp != NULL)
		{
			for (int n = 0; n != this->m_size && n != Obj.m_size; n++, Temp = Temp->get_Next(), TempObj = TempObj->get_Next())
			{
				Temp->set_Data(TempObj->data_Read());
			}//将本链已有空间填入作用链数据
			if (this->m_size < Obj.m_size)//如果本链大小不足
				for (int n = m_size; n != Obj.m_size; n++, TempObj = TempObj->get_Next())
					Append(TempObj->data_Read());//在本链内追加新空间
			else if (this->m_size > Obj.m_size)//如果本链大于作用链
			{
				for (int n = m_size; n != Obj.m_size; n--)//删除超长的位置。
					Delete(n);
			}
		}
		else
		{
			for (int n = 0; n != Obj.Size(); n++)
				this->Append(Obj[n]);
		}
	}
	template<class TYPE>
	const TYPE& Chain<TYPE>::operator [](int Index) const
	{
		return this->Locate(Index)->data_Read();
	}
	template<class TYPE>
	Chain<TYPE>& Chain<TYPE>::operator+=(const Chain<TYPE>& Obj)
	{
		for (int n= 0;n!=Obj.Size();n++)
		{
			this->Append(Obj[n]);
		}
		return *this;
	}
	template<class TYPE>
	Chain<TYPE>& Chain<TYPE>::operator+=(const TYPE& Obj)
	{
		this->Append(Obj);
	}
}
#endif