#ifndef DEBUG_H
#define DEBUG_H

//TODO define debug levels
#define NOOS_DEBUG

#ifdef NOOS_DEBUG
#define ASSERT_AND_RET(ret, error_msg) do {\
		if (IS_ERR_VALUE(ret)) {\
			printf("Assert fail: %s -- Code (-0x%x)\n", (error_msg),\
			-ret);\
			return (ret);\
		}\
	} while (0)

#define ASSERT_AND_EXIT(ret, error_msg) do {\
		if (IS_ERR_VALUE(ret)) {\
			printf("Assert fail: %s code: %d (-0x%x)\n", (error_msg)\
			, (ret), (-(ret)));\
			goto exit;\
		}\
	} while (0)

#else
#define ASSERT_AND_RET(a, b)
#endif

#endif
