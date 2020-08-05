#ifndef TEXTURE_HPP 
#define TEXTURE_HPP

#include <map>

class Texture
{
public:
	Texture();
	~Texture();
	unsigned int load_texture(std::string filename);
	void activatetexture(int level,unsigned int id);
private:
	std::map<std::string, unsigned int> texture_map;
};



#endif // !
