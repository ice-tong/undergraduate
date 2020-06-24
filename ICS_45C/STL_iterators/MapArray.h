template <typename S, typename I>
class MapArray
{
    pair<S,I> * buf;
    int sz;

public:
    struct iterator
    {
	typedef random_access_iterator_tag iterator_category;
	typedef iterator self_type;
	typedef pair<S,I> value_type;
	typedef pair<S,I>& reference;
	typedef pair<S,I>* pointer;
    private:
	pair<S,I> * ibuf;
    public:
	iterator(pointer ptr) : ibuf(ptr) {}
	self_type operator++() {++ibuf; return *this;}
	reference operator*() {return *ibuf;}
	bool operator != (const self_type& rhs) const {return ibuf != rhs.ibuf;}
    };

    MapArray() : buf(new pair<S,I>[10000]), sz(0) {}
    
    void sort()
    {
	int j;
	pair<S,I> holder;
	for (int i = 1; i < sz; ++i)
	{
	    holder = buf[i];
	    j = i - 1;

	    while (j >= 0 && buf[j].first > holder.first)
	    {
		buf[j+1] = buf[j];
		--j;
	    }
	    buf[j+1] = holder;
	}
    }    

    I& operator [] (S index)
    {
	for (int i = 0; i < sz; ++i)
	    if (buf[i].first == index)
		return buf[i].second;
	buf[sz++].first = index;
	buf[sz].second = 0;
	sort();
	return buf[sz].second;
    }
    
    iterator begin() {return iterator(buf);}
    iterator end() {return iterator(buf + sz);}
    ~MapArray() {delete[] buf;}
};
