#include "asset.h"
#include<string>
using namespace std;

Asset::Asset(std::string id)
{

	_id = id;
}
Asset::~Asset() {}
string Asset::id()
{
	return _id;
}