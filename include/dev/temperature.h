#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#ifdef __cplusplus
extern "C"{
#endif

int     temperature_get_degrees_celsius    (void);
void    temperature_set_configuration      (unsigned reg_data);
void    temperature_set_high_limit         (unsigned reg_data);
void    temperature_set_low_limit          (unsigned reg_data);
int     temperature_init                   (void);

#ifdef __cplusplus
}
#endif

#endif /* _TEMPERATURE_H_*/
