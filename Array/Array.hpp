#ifndef ARRAY_HPP_INCLUDED
#define ARRAY_HPP_INCLUDED
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <cstdlib>
#define TPL template<typename T>
const int MULTIPLIER = 2;

/*
= -, == +, != +, < +, <= +, >+, >= +, []+. Функцию assign +, insert - , push_back+, pop_back+, clear+, at+.
*/
//exception handling
class Exception: public std::exception
{
    private:
        const char* ex_str;
    public:
        Exception()
        {}
        Exception(const char* str)
        {
            ex_str = str;
        }

        virtual ~Exception() throw()
        {}

        const char *what() const throw()
        {
            return ex_str;
        }
};
////////////////////////////////////////////////////////////////////////





TPL
//template<typename RAIterator>
class Array
{
    private:
        static const size_t INIT_SIZE = 10;
        T* data_;
        size_t pos;
        size_t size_;
        void Vector_resize (const int a);
        void Assert_OK()const;
        void copy(const Array<T>& that);
    public:
        //iterator classes
        class iterator;
        class reverse_iterator;
        ////////////////////////

        //array's iterators
        iterator begin()const
        {
            iterator that(data_);
            return that;
        }
        iterator end()const
        {
            iterator that(data_ + pos);
            return that;
        }
        reverse_iterator rbegin()const
        {
            if (!pos)
                return reverse_iterator(data_);
            return reverse_iterator(data_ + pos - 1);
        }

        reverse_iterator rend()const
        {
            if (!pos)
                return reverse_iterator(data_);
            return reverse_iterator(data_ - 1);
        }
        ////////////////////////

        //constructors // COW
        Array<T> (); //
        Array<T> (std::initializer_list<T> inp);
        Array<T> (size_t pos_, size_t value): data_(new T[pos_]), pos(0), size_(pos_)
        {
            assign(pos_, value);
        }
        Array<T> (const Array<T>& that);
        explicit Array<T> (size_t INIT_size); //
        ~Array<T> ();
        Array<T>& operator = (const Array<T>& vec);
        ////////////////////////

        //insert and assign methods
        void assign(size_t count, const T& value ); // first count values with value
        void assign(std::initializer_list<T> inp)
        {
            clear();
            for (auto iter = inp.begin(); iter != inp.end(); ++iter)
                push_back(*iter);
        }
        void assign(iterator beg_i, iterator end_i)
        {
            clear();
            for (auto iter = beg_i; iter != end_i; ++iter)
                push_back(*iter);
            ////////////
        }
        template<typename RAIterator>
        void insert( const RAIterator& posit, size_t count, const T& value ); //from posit insert count position with value
        template<typename RAIterator>
        void insert( const iterator& posit, const RAIterator& beg, const RAIterator& end);
        ////////////////////////


        //push/pop
        void push_back( const T& value ); //input elem to the end
        void pop_back(); //just pop last element delete it and so
        ////////////////////////


        //reference to elements
        const T& operator [] (const size_t ind)const;
        T& operator [] (const size_t ind);
        const T& at( size_t posisiton )const;
        T& at (size_t pos)
        {
            return (*this)[pos];
        }
        ////////////////////////

        //overloaded operators
        bool operator == (const Array<T>& that)const;
        bool operator < (const Array<T>& that)const;
        bool operator > (const Array<T>& that)const;
        bool operator >= (const Array<T>& that)const;
        bool operator <= (const Array<T>& that)const;
        bool operator != (const Array<T>& that)const;
        ////////////////////////

        //Debug checks and infos
        bool Vector_OK()const;
        void Array_Dump()const;
        ////////////////////////

        //other
        bool is_empty()const;
        void clear();
        size_t capacity()const
        {
            return size_;
        }
        size_t size()const
        {
            return pos;
        }
        ////////////////////////
};
////////////////////////////////////////////////////////////////////////

//iterator classes
TPL
class Array<T>::iterator
{
    private:
        T* vec_pointer;
    public:
        iterator(): vec_pointer(nullptr)
        {}
        using value_type = T;
        iterator(T* ptr): vec_pointer(ptr)
        {}
        iterator& operator++ ()
        {
            ++vec_pointer;
            return *this;
        }

        iterator& operator-- ()
        {
            --vec_pointer;
            return *this;
        }
		friend int operator - (iterator b, iterator a)
		{
			return distance(a, b);
		}
        iterator operator-- (int in)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator++ (int in)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        T& operator*()
        {
            return *vec_pointer;
        }
        const T* get()const
        {
            return vec_pointer;
        }
       // T* get()
       // {
        //    return vec_pointer;
        //}
        void operator = (const iterator& that)
        {
            vec_pointer = that.vec_pointer;
        }

        bool operator != (const iterator& rhs)const
        {
            return (vec_pointer != rhs.vec_pointer);
        }
        bool operator == (const iterator& rhs)const
        {
            return !(vec_pointer != rhs.vec_pointer);
        }
        iterator operator + (const size_t& ind)const
        {
            return vec_pointer + ind;
        }
        iterator operator - (const size_t& ind)const
        {
            return vec_pointer - ind;
        }
};


TPL
class Array<T>::reverse_iterator
{
    private:
        T* vec_pointer;
    public:
        reverse_iterator(): vec_pointer(nullptr)
        {}
        reverse_iterator(T* ptr): vec_pointer(ptr)
        {}
        reverse_iterator& operator++ ()
        {
            --vec_pointer;
            return *this;
        }
        reverse_iterator& operator-- ()
        {
            ++vec_pointer;
            return *this;
        }
        T& operator*()
        {
            return *vec_pointer;
        }
        const T* get()const
        {
            return vec_pointer;
        }
        void operator = (const reverse_iterator& that)
        {
            *vec_pointer = that.vec_pointer;
        }

        bool operator != (const reverse_iterator& rhs)const
        {
            return (vec_pointer != rhs.vec_pointer);
        }
        bool operator == (const reverse_iterator& rhs)const
        {
            return !(vec_pointer != rhs.vec_pointer);
        }
        reverse_iterator operator + (const size_t& ind)const
        {
            return vec_pointer - ind;
        }
};
////////////////////////////////////////////////////////////////////////

//constructors // COW
TPL
Array<T>::Array(size_t INIT_size): pos(INIT_size)
{
    size_ = (INIT_size);
    if (INIT_size <= 0)
        throw (Exception("Out of range in Constructor with INIT_size <= 0"));
    else
        data_ = new T[INIT_size];
    //for (auto i : (*this))
    for (iterator i = begin(); i != end(); ++i)
        *i = T(NULL);

}

TPL
Array<T>::Array (const Array<T>& that)
{
    size_ = that.size_;
    pos = that.pos;
    data_ = new T[that.size_];
    auto th_it = begin();
    for (auto it = that.begin(); it != that.end(); ++it, ++th_it)
    {
        *th_it = *it;
    }
    Assert_OK();
}

TPL
Array<T>::Array(std::initializer_list<T> inp):data_(new T[inp.size()]), pos(0), size_(inp.size())
{
    for (auto iter = inp.begin(); iter != inp.end(); ++iter)
        push_back(*iter);
}

TPL
Array<T>::Array(): pos(0), size_(INIT_SIZE)
{
    data_ = new T[INIT_SIZE];
}

TPL
Array<T>::~Array()
{
    delete[] data_;
    pos = 0;
    size_ = 0;
}

TPL
Array<T>& Array<T>::operator = (const Array<T>& vec)
{
    if (&vec != this)
        copy(vec);
    return *this;
}
////////////////////////////////////////////////////////////////////////

//insert and assign methods
TPL
template<typename RAIterator>
void Array<T>::insert( const RAIterator& posit, size_t count, const T& value )
{
    Array<T> res(pos + count);
    res.clear();
    for (auto it = begin(); it != posit; ++it)
    {
        res.push_back(*it);
    }
    //res.assign(count, value);
    for (size_t i = 0; i < count; i++)
        res.push_back(value);
    for (auto it = posit; it != end(); ++it)
        res.push_back(*it);
    *this = res;
}

TPL
template<typename RAIterator>
void Array<T>::insert( const iterator& posit, const RAIterator& beg, const RAIterator& last)
{
    Array<T> res(pos + (last - beg)); //////////////////!!!!!!!!!!!!!!
    res.clear();
    for (auto it = begin(); it != posit; ++it)
    {
         res.push_back(*it);
    }
    for (auto out_iter = beg; out_iter != last; out_iter++)
    {
        res.push_back(*out_iter);
    }
    for (auto it = posit; it != end(); ++it)
        res.push_back(*it);
    *this = res;
}

TPL
void Array<T>::assign( const size_t count, const T& value)
{
    clear();
    for (size_t i = 0; i < count; i++)
        push_back(value);
}
////////////////////////////////////////////////////////////////////////

//push/pop
TPL
void Array<T>::push_back( const T& value )
{
    Assert_OK();
    if (pos == size_)
        Vector_resize(1);
    data_[pos++] = value;
    Assert_OK();
}

TPL
void Array<T>::pop_back()
{
    Assert_OK();
    if (pos == 0)
    {
        std::cout<<"Vector IS UNDERFLOW\n";
        exit(-1);
    }
    data_[--pos] = (T)NULL;

    Vector_resize(0);
    Assert_OK();
}
////////////////////////////////////////////////////////////////////////

//reference to elements
TPL
const T& Array<T>::at( size_t position )const
{
    return (*this)[position];
}

TPL
const T& Array<T>::operator [] (const size_t ind)const
{
    if ((is_empty()) || (ind < 0) || (ind >= pos))
        throw (Exception("Out of range, operator [] or at"));
    return data_[ind];
}

TPL
T& Array<T>::operator [] (const size_t ind)
{
    if ((is_empty()) || (ind < 0) || (ind >= pos))
        throw (Exception("Out of range, operator [] or at"));
    return data_[ind];
}
////////////////////////////////////////////////////////////////////////

//overloaded operators
TPL
bool Array<T>::operator < (const Array<T>& that)const
{
    if (size_ < that.size_)
        return true;
    if (size_ > that.size_)
        return false;
    bool fl = true;
    auto th_it = that.begin();
    auto it = begin();
    for(; th_it != that.end(); ++it, ++th_it)
        if (*it == *th_it)
        {
            continue;
        }
        else if (*it < *th_it)
        {
            fl = false;
            break;
        }
    return !fl;
}

TPL
bool Array<T>::operator > (const Array<T>& that)const
{
    return (that < *this);
}

TPL
bool Array<T>::operator >= (const Array<T>& that)const
{
    return (that < *this) || (that == *this);
}

TPL
bool Array<T>::operator <= (const Array<T>& that)const
{
    return (that >= *this);
}

TPL
bool Array<T>::operator == (const Array<T>& that)const
{
    bool fl = true;
    auto th_it = that.begin();
    auto it = begin();
    for(; ((th_it != that.end()) && (it != end())); ++it, ++th_it)
        if (*it != *th_it)
        {
            fl = false;
            break;
        }
    return (fl && (that.pos == pos));
}

TPL
bool Array<T>::operator != (const Array<T>& that)const
{
    return (!(*this == that));
}
////////////////////////////////////////////////////////////////////////

//Debug and system methods
TPL
bool Array<T>::Vector_OK()const
{
    ////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //////////////////////
    return (data_ && (!pos) && size_)||(!((data_ == NULL) || (pos < 0) || (this == NULL) || (size_ < 0) || (pos > size_)));
}

TPL
void Array<T>::Assert_OK()const
{
    if (!Vector_OK())
    {
        Array_Dump();
        assert(!"Bad object Vector");
    }
}

TPL
void Array<T>::Vector_resize (const int a)// a shows the type of resize: 0 for contraction and 1 for elongation
{

    Assert_OK();
    if (!size_)
        size_++;
    int new_size_ = size_;
    if ((a == 0) && (pos < 3*(size_)/8))
        new_size_ /= MULTIPLIER;
    if (a == 1)
        new_size_ *= MULTIPLIER;
    if (a || ((a == 0) && (pos < 3*(size_)/8)))
    {
        T* temp = new T[new_size_];
        for (size_t i = 0; i < pos; i++)
            temp[i] = data_[i];
        delete[] data_;
        data_ = temp;
    }
    size_ = new_size_;
    Assert_OK();
}

TPL
void Array<T>::copy(const Array<T>& that)
{
    delete[] data_;
    pos = that.pos;
    data_ = new T[size_ = that.size_];
    auto th_it = begin();
    for (auto it = that.begin(); it != that.end(); ++it, ++th_it)
    {
        *th_it = *it;
    }
}

TPL
void Array<T>::Array_Dump()const
{
    if (is_empty())
        std::cout<<"Vector is Empty!\n";
    else
    {
        for (size_t i = 0; i < pos; i++)
            std::cout<<data_[i]<<" data_["<<i<<"] "<<std::endl;
        std::cout<<"Addresses: &data = "<<&data_<<", &this = "<<this<<std::endl;
        std::cout<<"Number of elements = "<<pos<<std::endl;
    }
}
////////////////////////////////////////////////////////////////////////

//other
TPL
void Array<T>::clear()
{
    pos = 0;
}

TPL
bool Array<T>::is_empty()const
{
    return ((pos <= 0) || (size_ <= 0));
}

template <typename It>
long distance(It first, It last)
{
	long n = 0;
	while (last-- != first)
		n++;
	return n;
}
////////////////////////////////////////////////////////////////////////


#endif // ARRAY_HPP_INCLUDED
