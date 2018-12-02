#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm>
using std::copy;

template<typename dataType>
class vector
{
public:

    vector() : size_v{8}, elem(new dataType[8]), reservedSize{100} // default constructor
    {
        for(int i = 0; i < size_v; ++i)
        {
            elem[i] = dataType(); // elements are initialized
        }
    }

    vector(int size) : size_v{size}, elem(new dataType[size]), reservedSize{size} // alternate constructor
        {
            for(int i = 0; i < size_v; ++i)
            {
                elem[i] = dataType(); // elements are initialized
            }
        }

    vector(const vector<dataType> &copiedVector) : size_v{copiedVector.size_v}, elem{new dataType[copiedVector.size_v]}, reservedSize{copiedVector.reservedSize} // copy constructor
    {
        copy(copiedVector.elem, copiedVector.elem + size_v, elem); // copy elements - std::copy() algorithm
    }

    vector &operator=(const vector &copiedVector) // copy assignment
    {
        dataType *p = new dataType[copiedVector.size_v];       // allocate new space
        copy(copiedVector.elem, copiedVector.elem + copiedVector.size_v, p); // copy elements - std::copy() algorithm
        delete[] elem;                            // deallocate old space
        elem = p;                                 // now we can reset elem
        size_v = copiedVector.size_v;
        return *this;  // return a self-reference
    }

    ~vector()
    {
        delete[] elem; // deconstructor
    }

    dataType &operator[](int n)
    {
        return elem[n]; // access: return reference
    }

    const dataType &operator[](int n) const
    {
        return elem[n];
    }

    int size() const
    {
        return size_v;
    }

    int capacity() const
    {
        return reservedSize;
    }

    void resize(int newsize) // growth
    // make the vector have newsize elements
    // initialize each new element with the default value 0.0
    {
        reserve(newsize);
        for(int i = size_v; i < newsize; ++i)
        {
            elem[i] = 0; // initialize new elements
        }
        
        size_v = newsize;
    }

    void push_back(dataType d)
    // increase vector size by one; initialize the new element with d
    {
        if(reservedSize == 0)
        {
            reserve(100);         // start with space for 8 elements
        }
        else if(size_v == reservedSize)
        {
            reserve(2 * reservedSize); // get more space
        }
        
        elem[size_v] = d;       // add d at end
        ++size_v;               // increase the size (size_v is the number of elements)
    }

    void reserve(int newalloc)
    {
        if(newalloc <= reservedSize)
        {
            return;// never decrease allocation
        }

        dataType* p = new dataType[newalloc]; // allocate new space

        for(int i = 0; i < size_v; ++i) // copy old elements
        {
            p[i] = elem[i];
        }

        delete [] elem; // deallocate old space
        elem = p;
        reservedSize = newalloc;
    }

    using iterator = dataType *;
    using const_iterator = const dataType *;

    iterator begin() // points to first element
    {
        if(size_v == 0)
        {
            return nullptr;
        }
        
        return &elem[0];
    }

    const_iterator begin() const
    {
        if(size_v == 0)
        {
            return nullptr;
        }
        
        return &elem[0];
    }

    iterator end() // points to one beyond the last element
    {
        if(size_v == 0)
        {
            return nullptr;
        }
        
        return &elem[size_v];
    }

    const_iterator end() const
    {
        if(size_v == 0)
        {
            return nullptr;
        }
        
        return &elem[size_v];
    }

    iterator insert(iterator p, const dataType &val) // insert a new element val before p
    {
        int index = p - begin();
        
        if(size() == capacity())
        {
            reserve(size() == 0 ? 8: 2*size());// make sure we have space
        }
        
        ++size_v;
        iterator pp = begin() + index; // the place to put value

        for(iterator pos = end() - 1; pos != pp; --pos)
        {
            *pos = *(pos - 1);// copy element one position to the right

        }

        *(begin() + index) = val; // insert value

        return pp;
    }

    iterator erase(iterator p) // remove element pointed to by p
    {
        if(p == end())
        {
            return p;
        }
        
        for (iterator pos = p + 1; pos != end(); ++pos)
        {
            *(pos - 1) = *pos; // copy element one position to the left
        }
        
        delete (end() - 1);
        --size_v;
        return p;
    }

private:

    int       size_v;        // Variable for vector size
    dataType* elem;          // Pointer variable to the elements (or 0)
    int       reservedSize;  // Variable for number of elements plus number of free slots

};


#endif /* VECTOR_H_ */
