#include "mesh_utils.h"

void mesh_utils::RenderMeshList(std::vector<Mesh*> meshList){
    for (Mesh* _mesh : meshList)
		_mesh->RenderMesh();
}