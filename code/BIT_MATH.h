#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG, BIT)    ((REG) |= (1 << (BIT)))
#define CLR_BIT(REG, BIT)    ((REG) &= ~(1 << (BIT)))
#define TOGGLE_BIT(REG, BIT) ((REG) ^= (1 << (BIT)))
#define GET_BIT(REG, BIT)    (((REG) >> (BIT)) & 1)
#define BIT_IS_SET(REG, BIT) (((REG) & (1 << (BIT))) != 0)
#define BIT_IS_CLEAR(REG, BIT) (!((REG) & (1 << (BIT))))

#endif /* BIT_MATH_H_ */
