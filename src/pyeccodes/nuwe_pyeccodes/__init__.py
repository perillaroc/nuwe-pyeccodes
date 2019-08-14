# coding: utf-8
from ._pyeccodes import *

key_type_mapper = {
	GribKeyType.Long: int,
	GribKeyType.Double: float,
	GribKeyType.String: str,
}

def codes_get(h, key, key_type = None):
	if key_type is None:
		key_type_id = get_native_type(h, key)
		if key_type_id in key_type_mapper:
			key_type = key_type_mapper[key_type_id]

	result = None
	if key_type == int:
		result = codes_get_long(h, key)
	elif key_type == float:
		result = codes_get_double(h, key)
	elif key_type == str:
		result = codes_get_string(h, key)
	
	return result

def codes_release(h):
	grib_handler_release(h)
