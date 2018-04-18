#include "DBO.h"

INT32 InitDBO(sql::Connection * conn) {
	INT32 result = InitItemsDBO(conn);
	if (result) {
		return 1;
	}

	return 0;
}
