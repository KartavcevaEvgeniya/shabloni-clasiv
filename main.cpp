#include <iostream>
using namespace std;
template<class T>
class Array
{
    T* arr;
    int rows, cols, count, grow;

public:
    Array(int c = 3)
    {
        arr = nullptr;
        rows = 0;
        cols = c > 0 ? c : 3;
        count = 0;
        grow = 1;
    }

    Array(const Array& obj)
    {
        cols = obj.cols;
        rows = obj.rows;
        count = obj.count;
        grow = obj.grow;

        arr = new T[rows * cols]{};

        for (int i = 0; i < count; i++)
        {    
            arr[i] = obj.arr[i];
        }
    }

    ~Array()
    {
        delete[] arr;
    }

    int GetSize()
    {
        return rows * cols;
    }

    void SetSize(int size, int g = 1)
    {
        if (size < 0) {return;}
        if (g > 0) { grow = g;}

        int r = (size + cols - 1) / cols;
        int newSize = r * cols;

        T* temp = new T[newSize]{};
        int n = count < size ? count : size;

        for (int i = 0; i < n; i++)
        {    
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        rows = r;
        count = n;
    }

    int GetUpperBound()
    {
        return count - 1;
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    void FreeExtra()
    {
        SetSize(count, grow);
    }

    void RemoveAll()
    {
        delete[] arr;
        arr = nullptr;
        rows = 0;
        count = 0;
    }

    T GetAt(int r, int c)
    {
        return arr[r * cols + c];
    }

    void SetAt(int r, int c, T value)
    {
        arr[r * cols + c] = value;
    }

    T* operator[](int i)
    {
        return arr + i * cols;
    }

    void Add(T value)
    {
        if (count == GetSize())
        {    
            SetSize(GetSize() + grow * cols, grow);
        }

        arr[count] = value;
        count++;
    }

    void Append(const Array& obj)
    {
        if (this == &obj)
        {
            Array temp(obj);
            Append(temp);
            return;
        }

        for (int i = 0; i < obj.count; i++)
        {    
            Add(obj.arr[i]);
        }
    }

    Array& operator=(const Array& obj)
    {
        if (this != &obj)
        {
            delete[] arr;

            rows = obj.rows;
            cols = obj.cols;
            count = obj.count;
            grow = obj.grow;

            arr = new T[rows * cols]{};

            for (int i = 0; i < count; i++)
            {    
                arr[i] = obj.arr[i];
            }
        }

        return *this;
    }

    T* GetData()
    {
        return arr;
    }

    void InsertAt(int index, T value)
    {
        if (index < 0 || index > count) {return;}
        Add(value);
        for (int i = count - 1; i > index; i--)
        {    
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
    }

    void RemoveAt(int index)
    {
        if (index < 0 || index >= count) {return;}
        for (int i = index; i < count - 1; i++)
        {    
            arr[i] = arr[i + 1];
        }
        count--;
    }

    void Output()
    {
        for (int i = 0; i < count; i++)
        {
            cout << arr[i] << " ";
            if ((i + 1) % cols == 0)
            {    
                cout << endl;
            }
        }
        if (count % cols != 0)
        {    
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    Array<int> obj1;
    for (int i = 1; i <= 6; i++)
    {    
        obj1.Add(i);
    }
    obj1.Output();

    obj1.SetAt(0, 1, 10);
    obj1.Output();

    cout << obj1.GetAt(0, 1) << endl;
    cout << obj1.GetSize() << endl;
    cout << obj1.GetUpperBound() << endl;
    cout << obj1.IsEmpty() << endl;

    obj1[1][0] = 20;
    obj1.Output();

    Array<int> obj2;
    obj2.Add(7);
    obj2.Add(8);

    obj1.Append(obj2);
    obj1.Output();

    obj1.InsertAt(2, 100);
    obj1.Output();

    obj1.RemoveAt(2);
    obj1.Output();

    Array<int> rez = obj1;
    rez.FreeExtra();
    rez.Output();

    rez.SetSize(12, 2);
    cout << rez.GetSize() << endl;

    cout << rez.GetData()[0] << endl;

    rez.RemoveAll();
    cout << rez.IsEmpty() << endl;

    return 0;
}
