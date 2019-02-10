#pragma once

#define QUEUE_DATAMAX 50

template <class T>
class CQueue
{
private:
	int front;
	int rear;

	T Data[QUEUE_DATAMAX];
	int NextPosIdx(int* pos)
	{
		if (*pos == QUEUE_DATAMAX - 1)
			return 0;
		else
			*pos = (*pos + 1) % QUEUE_DATAMAX;
		return true;
	}
	bool Peek(T *out)
	{
		if (front == rear)
			return true;

		*out = NextPosIdx(front);
	}
public:

	CQueue();

	bool Dequeue(T *pData = nullptr);
	void Enqueue(T data);
	int getSize();
	int freeSize();
	bool Peek(T *out, int pos);
};

template <class T>
CQueue<T>::CQueue()
	:front(0), rear(0)
{
}


template <class T>
void CQueue<T>::Enqueue(T data)
{
	if ((rear + 1) % QUEUE_DATAMAX != front)
	{
		Data[rear] = data;
		rear = (rear + 1) % QUEUE_DATAMAX;
	}
}

template <class T>
bool CQueue<T>::Dequeue(T *pData)
{
	
	if (front != rear)
	{
		if(pData != nullptr)
			*pData = Data[front];
		
		front = (front + 1) % QUEUE_DATAMAX;

		return true;
	}
	return false;
}

template <class T>
int CQueue<T>::getSize()
{
	if (front < rear)
		return rear - front ;
	else if ((rear + 1) % QUEUE_DATAMAX == front)
		return QUEUE_DATAMAX - 1;
	else
		return (QUEUE_DATAMAX - ((QUEUE_DATAMAX - front) + (rear + 1)));
}


template <class T>
int CQueue<T>::freeSize()
{
	return (QUEUE_DATAMAX - 1) - getSize();
}

template <class T>
bool CQueue<T>::Peek(T *out, int pos)
{
	if (front != rear)
	{
		int tFront = front;

		tFront = (tFront + pos) % QUEUE_DATAMAX;

		if (tFront != rear)
		{
			*out = Data[tFront];
			return true;
		}
	}
	return false;
}