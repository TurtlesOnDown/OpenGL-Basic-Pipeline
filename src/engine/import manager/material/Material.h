#include "../../objects/Component.h"

#include "../shader/Shader.h"
#include "../texture2D/Texture2D.h"

#ifndef MATERIALCLASS
#define MATERIALCLASS

// Material class to contain textures and parameters

class Material : public Component {
public:
	Material();
	~Material();
	Material operator=(const Material& m);

	void addTexture2D(std::string name, const std::shared_ptr<Texture2D> t);

	void useMaterial(const std::shared_ptr<Shader> s);

private:
	std::map<std::string, std::shared_ptr<Texture2D>> textures2D;
};

#endif // !MATERIALCLASS

