#include <map>
using namespace std;

template <typename K, typename V>
V getWithDefault(const  map <K, V> & m, const K & key, const V & defval) {
	typename map<K, V>::const_iterator it = m.find(key);
	if (it == m.end()) {
		return defval;
	}
	else {
		return it->second;
	}
}