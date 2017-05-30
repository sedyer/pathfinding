#pragma once

template <typename K, typename V>
	V getWithDefault(const map<K,V> & map, const K & key, const V & default) {

		if (map.find(key) == map.end()) {
			return default;
		}
		else {
			return iterator->second;
		}
	}

