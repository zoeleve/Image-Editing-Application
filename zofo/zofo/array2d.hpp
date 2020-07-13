/*! Returns the width of the array
*/
template <typename T>
const unsigned int math::Array2D<T>::getWidth() const {
	return this->width;
}
		
/*! Returns the height of the array
*/
template <typename T>
const unsigned int math::Array2D<T>::getHeight() const {
	return this->height;
}

// data accessors and mutators
		
/*! Obtains a pointer to the internal data.
*
*  This is NOT a copy of the internal array data, but rather a pointer 
*  to the internally allocated space, so DO NOT attempt to delete the pointer. 
*/
template <typename T>
T * math::Array2D<T>::getRawDataPtr() {
	return this->buffer.data();
}

/*! Copies the array data from an external raw buffer to the internal array buffer. 
*
*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the 
*  Array2D object. If the array buffer cannot be properly resized or the width or height of the array are 0, 
*  the method should exit immediately.
*
*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Array2D object.
*/
template <typename T>
void math::Array2D<T>::setData(const T * const & data_ptr) {
	if (data_ptr != 0) {
		for (unsigned int i=0;i<(this->width)*(this->height);i++) {
			buffer[i] = data_ptr[i];
		}
	}
}

/*! Returns a reference to the stored item at location (x,y).
*
*	\param x is the horizontal coordinate of the item.
*  \param y is the vertical coordinate of the item.
*
*  \return a reference to the item at location (x,y).
*/
template <typename T>
T & math::Array2D<T>::operator () (unsigned int x, unsigned int y) {
	unsigned int i = x + y*width;
	return buffer[i];
}

// constructors and destructor

/*! Constructor with data initialization.
* 
* Default parameters let it also be used as a default constructor.
*
//* \param width is the desired width of the new array.
* \param height is the desired height of the new array.
* \param data_ptr is the source of the data to copy to the internal array buffer. 
* If none is provided, but the width and height are non-zero, the buffer is initialized to default values (all zero - black).
* 
* \see setData
*/ 
template <typename T>
math::Array2D<T>::Array2D(unsigned int width , unsigned int height , const T * data_ptr ) : width(width), height(height) {
	if (data_ptr != 0) {
		buffer.reserve(width*height);
		setData(data_ptr);
	} else {
		if (width != 0 && height != 0) {
			buffer.reserve(width*height);			
		}
	}
}
		
/*! Copy constructor.
*
* \param src is the source array to replicate in this object.
*/
template <typename T>
math::Array2D<T>::Array2D(const Array2D &src) : width(src.width), height(src.height) {
	if (src.buffer.size() > 0) {
		buffer.resize(width*height);
		setData(src.buffer.data());
	}
}
		
/*! The Array2D destructor.
*/
template <typename T>
math::Array2D<T>::~Array2D() {
	buffer.clear();
}

/*! Copy assignment operator.
*
* \param right is the source array.
*/
template <typename T>
math::Array2D<T> & math::Array2D<T>::operator=(const math::Array2D<T> & right) {
	if (this->width == right.width && this->height == right.height) { // equal dimensions
		setData(right.data_ptr);
	} else {
		this->width = right.width;
		this->height = right.height;

		buffer.clear();
		buffer.resize(width*height);
		setData(right.data_ptr);
	}

	return *this;
}
