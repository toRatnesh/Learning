/********
    Example 
    Proxy Design Pattern: Implementation of virtual proxy	
	
*************/

#include <iostream>
#include <string>

class ImageInterface {
    protected:
        ImageInterface() { 
            //std::cout << "ImageInterface()\n";
        }

    public:
        virtual ~ImageInterface() { 
            //std::cout << "~ImageInterface()\n";
        }
        virtual void draw() = 0;
        virtual int getId() = 0;
};

class RealImage : public ImageInterface {
    std::string     m_filename;
    int             m_id;

    public:
        virtual ~RealImage() {
            std::cout << "~RealImage()\n";
        }
        RealImage(std::string filename, int id) 
            : m_filename(filename), m_id(id) { 
                std::cout << "RealImage()\n";
        }

        virtual void draw(){ 
            std::cout << "drawing image-" << getId() << '\n'; 
        }
        virtual int getId() { 
            return m_id; 
        }
};

class ProxyImage : public ImageInterface {
        RealImage * image = nullptr;

        std::string     m_filename;
        int             m_id;
    protected:
        RealImage * getImage() {
            if(nullptr == image) {
                image = new RealImage(m_filename, m_id);
            }
            return image;
        }
    public:
        virtual ~ProxyImage() {
            if(nullptr != image) {
                delete image;
                image = nullptr;
            }
        }
        ProxyImage(std::string filename, int id)
            : m_filename(filename), m_id(id) { }

        virtual void draw(){ 
            getImage()->draw();
        }
        virtual int getId() { 
            if(image) {
                return image->getId();
            }
            return m_id;
        }
};

int main() {
    {
        std::cout << "=== Without Proxy ===\n";

        ImageInterface * ptr = new RealImage("sample_file", 4);
        ptr->draw();
        delete ptr; ptr = nullptr;
        
        std::cout << '\n';
        RealImage iarr[] = {RealImage("sample_file", 1), RealImage("sample_file", 2), RealImage("sample_file", 3)};
        for(int i = 0; i < 3; ++i) {
            iarr[i].draw();
        }        
    }
    
    {
        std::cout << "\n=== With Proxy ===\n";

        ImageInterface * ptr = new ProxyImage("sample_file", 3);
        ptr->draw();
        delete ptr; ptr = nullptr;

        std::cout << '\n';
        ProxyImage parr[] = {ProxyImage("sample_file", 1), ProxyImage("sample_file", 2), ProxyImage("sample_file", 3)};
        for(int i = 0; i < 3; ++i) {
            parr[i].draw();
        }

    }

    return 0;
}

/********

Output:
=== Without Proxy ===
RealImage()
drawing image-4
~RealImage()

RealImage()
RealImage()
RealImage()
drawing image-1
drawing image-2
drawing image-3
~RealImage()
~RealImage()
~RealImage()

=== With Proxy ===
RealImage()
drawing image-3
~RealImage()

RealImage()
drawing image-1
RealImage()
drawing image-2
RealImage()
drawing image-3
~RealImage()
~RealImage()
~RealImage()




*********
    END OF FILE
*************/


