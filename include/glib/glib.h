#ifndef _NAGLIB_H_
#define	_NAGLIB_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#define g_memmove(dest,src,len) { memmove ((dest), (src), (len)); }

// future remove: g_log, g_strerror, g_set_error

//#define NAGLIB_PIPE_USE

typedef char   gchar;
typedef short  gshort;
typedef long   glong;
typedef int    gint;
typedef gint   gboolean;
typedef unsigned char   guchar;
typedef unsigned short  gushort;
typedef unsigned long   gulong;
typedef unsigned int    guint;
typedef float   gfloat;
typedef double  gdouble;
typedef struct _GTimeVal GTimeVal;
struct _GTimeVal {
  glong tv_sec;
  glong tv_usec;
};

typedef uint32_t guint32;
typedef uint64_t guint64;
typedef guint32 GQuark;
typedef void *gpointer;
typedef size_t gsize;

typedef void            (*GDestroyNotify)       (gpointer       data);
#define GLIB_VAR extern

#define _GAsyncQueue_Maximum 256
#define _GAsyncQueue_End (_GAsyncQueue_Maximum - 1)
//typedef void(*GDestroyNotify)(gpointer data);
#define NAGLIB_STATUS_EMPTY	0
#define NAGLIB_STATUS_PUSH	1
#define NAGLIB_STATUS_POP	2
typedef struct _GAsyncQueue {
#ifdef NAGLIB_PIPE_USE
    int pipefd[2];
#endif
	pthread_mutex_t mutex;
	gpointer aData[_GAsyncQueue_Maximum];
//	GDestroyNotify freeFunction[_GAsyncQueue_Maximum];
	unsigned char pop;
	unsigned char push;
	unsigned char status[_GAsyncQueue_Maximum];
	int unref;
	int isFull;
// statistics
	int countPush;
	int countPop;
} GAsyncQueue;
typedef enum {
G_LOG_FLAG_RECURSION          = 1 << 0,
G_LOG_FLAG_FATAL              = 1 << 1,
G_LOG_LEVEL_ERROR             = 1 << 2,
G_LOG_LEVEL_CRITICAL          = 1 << 3,
G_LOG_LEVEL_WARNING           = 1 << 4,
G_LOG_LEVEL_MESSAGE           = 1 << 5,
G_LOG_LEVEL_INFO              = 1 << 6,
G_LOG_LEVEL_DEBUG             = 1 << 7,
G_LOG_LEVEL_MASK              = ~(G_LOG_FLAG_RECURSION | G_LOG_FLAG_FATAL)
} GLogLevelFlags;
typedef struct _GError {
	GQuark       domain;
	gint         code;
	gchar       *message;
} GError;

extern void g_usleep(gulong microseconds);

extern void g_log(const gchar *log_domain, GLogLevelFlags log_level, const gchar *format, ...);

extern const gchar *g_strerror(gint errnum);
extern void g_set_error(GError **err, GQuark domain, gint code, const gchar *format, ...);

extern void g_return_if_fail_warning (const char *log_domain, const char *pretty_function, const char *expression);

extern void g_free(gpointer mem);
extern gpointer g_malloc(gsize n_bytes);
extern gpointer g_malloc0(gsize n_bytes);
#define g_new0(struct_type,n_structs) ((struct_type *) g_malloc0(((gsize) sizeof (struct_type)) * ((gsize) (n_structs))))
extern gpointer g_slice_alloc(gsize n_bytes);
extern gpointer g_slice_alloc0(gsize n_bytes);
extern void g_slice_free1(gsize block_size, gpointer mem_block);
extern void g_slice_free(gsize block_size, gpointer mem_block);
extern gpointer g_realloc(gpointer mem, gsize n_bytes);

extern gint g_async_queue_length(GAsyncQueue *queue);
extern GAsyncQueue *g_async_queue_new(void);
extern void g_async_queue_unref(GAsyncQueue *queue);
extern gpointer g_async_queue_pop(GAsyncQueue *queue);
extern gpointer g_async_queue_try_pop(GAsyncQueue *queue);
extern void g_async_queue_push(GAsyncQueue *queue, gpointer data);

//==> #include <gthread.h>

//#include <glib/gerror.h>
//#include <glib/gtypes.h>
//#include <glib/gutils.h>        /* for G_INLINE_FUNC */
//#include <glib/gatomic.h>       /* for g_atomic_pointer_get */

extern GQuark g_thread_error_quark (void);
#define G_THREAD_ERROR g_thread_error_quark ()

typedef enum
{
  G_THREAD_ERROR_AGAIN /* Resource temporarily unavailable */
} GThreadError;

typedef gpointer (*GThreadFunc) (gpointer data);

typedef enum
{
  G_THREAD_PRIORITY_LOW,
  G_THREAD_PRIORITY_NORMAL,
  G_THREAD_PRIORITY_HIGH,
  G_THREAD_PRIORITY_URGENT
} GThreadPriority;

typedef struct _GThread         GThread;
struct  _GThread
{
  /*< private >*/
  GThreadFunc func;
  gpointer data;
  gboolean joinable;
  GThreadPriority priority;
};

typedef pthread_mutex_t			GMutex;	//typedef struct _GMutex          GMutex;
typedef struct _GCond           GCond;
typedef struct _GPrivate        GPrivate;
typedef struct _GStaticPrivate  GStaticPrivate;

typedef struct _GThreadFunctions GThreadFunctions;
struct _GThreadFunctions
{
  GMutex*  (*mutex_new)           (void);
  void     (*mutex_lock)          (GMutex               *mutex);
  gboolean (*mutex_trylock)       (GMutex               *mutex);
  void     (*mutex_unlock)        (GMutex               *mutex);
  void     (*mutex_free)          (GMutex               *mutex);
  GCond*   (*cond_new)            (void);
  void     (*cond_signal)         (GCond                *cond);
  void     (*cond_broadcast)      (GCond                *cond);
  void     (*cond_wait)           (GCond                *cond,
                                   GMutex               *mutex);
  gboolean (*cond_timed_wait)     (GCond                *cond,
                                   GMutex               *mutex,
                                   GTimeVal             *end_time);
  void      (*cond_free)          (GCond                *cond);
  GPrivate* (*private_new)        (GDestroyNotify        destructor);
  gpointer  (*private_get)        (GPrivate             *private_key);
  void      (*private_set)        (GPrivate             *private_key,
                                   gpointer              data);
  void      (*thread_create)      (GThreadFunc           func,
                                   gpointer              data,
                                   gulong                stack_size,
                                   gboolean              joinable,
                                   gboolean              bound,
                                   GThreadPriority       priority,
                                   gpointer              thread,
                                   GError              **error);
  void      (*thread_yield)       (void);
  void      (*thread_join)        (gpointer              thread);
  void      (*thread_exit)        (void);
  void      (*thread_set_priority)(gpointer              thread,
                                   GThreadPriority       priority);
  void      (*thread_self)        (gpointer              thread);
  gboolean  (*thread_equal)       (gpointer              thread1,
				   gpointer              thread2);
};

GLIB_VAR GThreadFunctions       g_thread_functions_for_glib_use;
GLIB_VAR gboolean               g_thread_use_default_impl;
GLIB_VAR gboolean               g_threads_got_initialized;

GLIB_VAR guint64   (*g_thread_gettime) (void);

extern void g_thread_init_glib (void);

/* initializes the mutex/cond/private implementation for glib, might
 * only be called once, and must not be called directly or indirectly
 * from another glib-function, e.g. as a callback.
 */
void    g_thread_init   (GThreadFunctions       *vtable);

/* Errorcheck mutexes. If you define G_ERRORCHECK_MUTEXES, then all
 * mutexes will check for re-locking and re-unlocking */

/* Initialize thread system with errorcheck mutexes. vtable must be
 * NULL. Do not call directly. Use #define G_ERRORCHECK_MUTEXES
 * instead.
 */
void    g_thread_init_with_errorcheck_mutexes (GThreadFunctions* vtable);

/* Checks if thread support is initialized.  Identical to the
 * g_thread_supported macro but provided for language bindings.
 */
gboolean g_thread_get_initialized (void);

/* A random number to recognize debug calls to g_mutex_... */
#define G_MUTEX_DEBUG_MAGIC 0xf8e18ad7

#ifdef G_ERRORCHECK_MUTEXES
#define g_thread_init(vtable) g_thread_init_with_errorcheck_mutexes (vtable)
#endif

/* internal function for fallback static mutex implementation */
GMutex* g_static_mutex_get_mutex_impl   (GMutex **mutex);

#define g_static_mutex_get_mutex_impl_shortcut(mutex) \
  (g_atomic_pointer_get (mutex) ? *(mutex) : \
   g_static_mutex_get_mutex_impl (mutex))

/* shorthands for conditional and unconditional function calls */

#define G_THREAD_UF(op, arglist)					\
    (*g_thread_functions_for_glib_use . op) arglist
#define G_THREAD_CF(op, fail, arg)					\
    (g_thread_supported () ? G_THREAD_UF (op, arg) : (fail))
#define G_THREAD_ECF(op, fail, mutex, type)				\
    (g_thread_supported () ? 						\
      ((type(*)(GMutex*, const gulong, gchar const*))			\
      (*g_thread_functions_for_glib_use . op))				\
     (mutex, G_MUTEX_DEBUG_MAGIC, G_STRLOC) : (fail))

#ifndef G_ERRORCHECK_MUTEXES
# define g_mutex_lock(mutex)						\
    G_THREAD_CF (mutex_lock,     (void)0, (mutex))
# define g_mutex_trylock(mutex)						\
    G_THREAD_CF (mutex_trylock,  TRUE,    (mutex))
# define g_mutex_unlock(mutex)						\
    G_THREAD_CF (mutex_unlock,   (void)0, (mutex))
# define g_mutex_free(mutex)						\
    G_THREAD_CF (mutex_free,     (void)0, (mutex))
# define g_cond_wait(cond, mutex)					\
    G_THREAD_CF (cond_wait,      (void)0, (cond, mutex))
# define g_cond_timed_wait(cond, mutex, abs_time)			\
    G_THREAD_CF (cond_timed_wait, TRUE,   (cond, mutex, abs_time))
#else /* G_ERRORCHECK_MUTEXES */
# define g_mutex_lock(mutex)						\
    G_THREAD_ECF (mutex_lock,    (void)0, (mutex), void)
# define g_mutex_trylock(mutex)						\
    G_THREAD_ECF (mutex_trylock, TRUE,    (mutex), gboolean)
# define g_mutex_unlock(mutex)						\
    G_THREAD_ECF (mutex_unlock,  (void)0, (mutex), void)
# define g_mutex_free(mutex)						\
    G_THREAD_ECF (mutex_free,    (void)0, (mutex), void)
# define g_cond_wait(cond, mutex)					\
    (g_thread_supported () ? ((void(*)(GCond*, GMutex*, gulong, gchar*))\
      g_thread_functions_for_glib_use.cond_wait)			\
        (cond, mutex, G_MUTEX_DEBUG_MAGIC, G_STRLOC) : (void) 0)
# define g_cond_timed_wait(cond, mutex, abs_time)			\
    (g_thread_supported () ?						\
      ((gboolean(*)(GCond*, GMutex*, GTimeVal*, gulong, gchar*))	\
        g_thread_functions_for_glib_use.cond_timed_wait)		\
          (cond, mutex, abs_time, G_MUTEX_DEBUG_MAGIC, G_STRLOC) : TRUE)
#endif /* G_ERRORCHECK_MUTEXES */

#define g_thread_supported()    (g_threads_got_initialized)
#define g_mutex_new()            G_THREAD_UF (mutex_new,      ())
#define g_cond_new()             G_THREAD_UF (cond_new,       ())
#define g_cond_signal(cond)      G_THREAD_CF (cond_signal,    (void)0, (cond))
#define g_cond_broadcast(cond)   G_THREAD_CF (cond_broadcast, (void)0, (cond))
#define g_cond_free(cond)        G_THREAD_CF (cond_free,      (void)0, (cond))
#define g_private_new(destructor) G_THREAD_UF (private_new, (destructor))
#define g_private_get(private_key) G_THREAD_CF (private_get, \
                                                ((gpointer)private_key), \
                                                (private_key))
#define g_private_set(private_key, value) G_THREAD_CF (private_set, \
                                                       (void) (private_key = \
                                                        (GPrivate*) (value)), \
                                                       (private_key, value))
#define g_thread_yield()              G_THREAD_CF (thread_yield, (void)0, ())

#define g_thread_create(func, data, joinable, error)			\
  (g_thread_create_full (func, data, 0, joinable, FALSE, 		\
                         G_THREAD_PRIORITY_NORMAL, error))

GThread* g_thread_create_full  (GThreadFunc            func,
                                gpointer               data,
                                gulong                 stack_size,
                                gboolean               joinable,
                                gboolean               bound,
                                GThreadPriority        priority,
                                GError               **error);
GThread* g_thread_self         (void);
void     g_thread_exit         (gpointer               retval);
gpointer g_thread_join         (GThread               *thread);

void     g_thread_set_priority (GThread               *thread,
                                GThreadPriority        priority);

/* GStaticMutexes can be statically initialized with the value
 * G_STATIC_MUTEX_INIT, and then they can directly be used, that is
 * much easier, than having to explicitly allocate the mutex before
 * use
 */
#if 0
#define g_static_mutex_lock(mutex) \
    g_mutex_lock (g_static_mutex_get_mutex (mutex))
#define g_static_mutex_trylock(mutex) \
    g_mutex_trylock (g_static_mutex_get_mutex (mutex))
#define g_static_mutex_unlock(mutex) \
    g_mutex_unlock (g_static_mutex_get_mutex (mutex))
void g_static_mutex_init (GStaticMutex *mutex);
void g_static_mutex_free (GStaticMutex *mutex);

struct _GStaticPrivate
{
  /*< private >*/
  guint index;
};
#define G_STATIC_PRIVATE_INIT { 0 }
void     g_static_private_init           (GStaticPrivate   *private_key);
gpointer g_static_private_get            (GStaticPrivate   *private_key);
void     g_static_private_set            (GStaticPrivate   *private_key,
					  gpointer          data,
					  GDestroyNotify    notify);
void     g_static_private_free           (GStaticPrivate   *private_key);

typedef struct _GStaticRecMutex GStaticRecMutex;
struct _GStaticRecMutex
{
  /*< private >*/
  GStaticMutex mutex;
  guint depth;
  GSystemThread owner;
};

#define G_STATIC_REC_MUTEX_INIT { G_STATIC_MUTEX_INIT }
void     g_static_rec_mutex_init        (GStaticRecMutex *mutex);
void     g_static_rec_mutex_lock        (GStaticRecMutex *mutex);
gboolean g_static_rec_mutex_trylock     (GStaticRecMutex *mutex);
void     g_static_rec_mutex_unlock      (GStaticRecMutex *mutex);
void     g_static_rec_mutex_lock_full   (GStaticRecMutex *mutex,
                                         guint            depth);
guint    g_static_rec_mutex_unlock_full (GStaticRecMutex *mutex);
void     g_static_rec_mutex_free        (GStaticRecMutex *mutex);

typedef struct _GStaticRWLock GStaticRWLock;
struct _GStaticRWLock
{
  /*< private >*/
  GStaticMutex mutex;
  GCond *read_cond;
  GCond *write_cond;
  guint read_counter;
  gboolean have_writer;
  guint want_to_read;
  guint want_to_write;
};

#define G_STATIC_RW_LOCK_INIT { G_STATIC_MUTEX_INIT, NULL, NULL, 0, FALSE, 0, 0 }

void      g_static_rw_lock_init           (GStaticRWLock* lock);
void      g_static_rw_lock_reader_lock    (GStaticRWLock* lock);
gboolean  g_static_rw_lock_reader_trylock (GStaticRWLock* lock);
void      g_static_rw_lock_reader_unlock  (GStaticRWLock* lock);
void      g_static_rw_lock_writer_lock    (GStaticRWLock* lock);
gboolean  g_static_rw_lock_writer_trylock (GStaticRWLock* lock);
void      g_static_rw_lock_writer_unlock  (GStaticRWLock* lock);
void      g_static_rw_lock_free           (GStaticRWLock* lock);

void	  g_thread_foreach         	  (GFunc    	  thread_func,
					   gpointer 	  user_data);

typedef enum
{
  G_ONCE_STATUS_NOTCALLED,
  G_ONCE_STATUS_PROGRESS,
  G_ONCE_STATUS_READY  
} GOnceStatus;

typedef struct _GOnce GOnce;
struct _GOnce
{
  volatile GOnceStatus status;
  volatile gpointer retval;
};

#define G_ONCE_INIT { G_ONCE_STATUS_NOTCALLED, NULL }

gpointer g_once_impl (GOnce *once, GThreadFunc func, gpointer arg);

#ifdef G_ATOMIC_OP_MEMORY_BARRIER_NEEDED
# define g_once(once, func, arg) g_once_impl ((once), (func), (arg))
#else /* !G_ATOMIC_OP_MEMORY_BARRIER_NEEDED*/
# define g_once(once, func, arg) \
  (((once)->status == G_ONCE_STATUS_READY) ? \
   (once)->retval : \
   g_once_impl ((once), (func), (arg)))
#endif /* G_ATOMIC_OP_MEMORY_BARRIER_NEEDED */

/* initialize-once guards, keyed by value_location */
G_INLINE_FUNC gboolean  g_once_init_enter       (volatile gsize *value_location);
gboolean                g_once_init_enter_impl  (volatile gsize *value_location);
void                    g_once_init_leave       (volatile gsize *value_location,
                                                 gsize           initialization_value);
#if defined (G_CAN_INLINE) || defined (__G_THREAD_C__)
G_INLINE_FUNC gboolean
g_once_init_enter (volatile gsize *value_location)
{
  if G_LIKELY ((gpointer) g_atomic_pointer_get (value_location) != NULL)
    return FALSE;
  else
    return g_once_init_enter_impl (value_location);
}
#endif /* G_CAN_INLINE || __G_THREAD_C__ */

/* these are some convenience macros that expand to nothing if GLib
 * was configured with --disable-threads. for using StaticMutexes,
 * you define them with G_LOCK_DEFINE_STATIC (name) or G_LOCK_DEFINE (name)
 * if you need to export the mutex. With G_LOCK_EXTERN (name) you can
 * declare such an globally defined lock. name is a unique identifier
 * for the protected varibale or code portion. locking, testing and
 * unlocking of such mutexes can be done with G_LOCK(), G_UNLOCK() and
 * G_TRYLOCK() respectively.
 */
extern void glib_dummy_decl (void);
#define G_LOCK_NAME(name)               g__ ## name ## _lock
#ifdef  G_THREADS_ENABLED
#  define G_LOCK_DEFINE_STATIC(name)    static G_LOCK_DEFINE (name)
#  define G_LOCK_DEFINE(name)           \
    GStaticMutex G_LOCK_NAME (name) = G_STATIC_MUTEX_INIT
#  define G_LOCK_EXTERN(name)           extern GStaticMutex G_LOCK_NAME (name)

#  ifdef G_DEBUG_LOCKS
#    define G_LOCK(name)                G_STMT_START{             \
        g_log (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,                   \
               "file %s: line %d (%s): locking: %s ",             \
               __FILE__,        __LINE__, G_STRFUNC,              \
               #name);                                            \
        g_static_mutex_lock (&G_LOCK_NAME (name));                \
     }G_STMT_END
#    define G_UNLOCK(name)              G_STMT_START{             \
        g_log (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,                   \
               "file %s: line %d (%s): unlocking: %s ",           \
               __FILE__,        __LINE__, G_STRFUNC,              \
               #name);                                            \
       g_static_mutex_unlock (&G_LOCK_NAME (name));               \
     }G_STMT_END
#    define G_TRYLOCK(name)                                       \
        (g_log (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,                  \
               "file %s: line %d (%s): try locking: %s ",         \
               __FILE__,        __LINE__, G_STRFUNC,              \
               #name), g_static_mutex_trylock (&G_LOCK_NAME (name)))
#  else  /* !G_DEBUG_LOCKS */
#    define G_LOCK(name) g_static_mutex_lock       (&G_LOCK_NAME (name))
#    define G_UNLOCK(name) g_static_mutex_unlock   (&G_LOCK_NAME (name))
#    define G_TRYLOCK(name) g_static_mutex_trylock (&G_LOCK_NAME (name))
#  endif /* !G_DEBUG_LOCKS */
#else   /* !G_THREADS_ENABLED */
#  define G_LOCK_DEFINE_STATIC(name)    extern void glib_dummy_decl (void)
#  define G_LOCK_DEFINE(name)           extern void glib_dummy_decl (void)
#  define G_LOCK_EXTERN(name)           extern void glib_dummy_decl (void)
#  define G_LOCK(name)
#  define G_UNLOCK(name)
#  define G_TRYLOCK(name)               (TRUE)
#endif  /* !G_THREADS_ENABLED */


#define  g_slice_new0(type)     ((type*) g_slice_alloc0 (sizeof (type)))



#endif

#ifdef __cplusplus
}
#endif

#endif


#if 0
/* Define min and max constants for the fixed size numerical types */
#define G_MININT8	((gint8)  0x80)
#define G_MAXINT8	((gint8)  0x7f)
#define G_MAXUINT8	((guint8) 0xff)

#define G_MININT16	((gint16)  0x8000)
#define G_MAXINT16	((gint16)  0x7fff)
#define G_MAXUINT16	((guint16) 0xffff)

#define G_MININT32	((gint32)  0x80000000)
#define G_MAXINT32	((gint32)  0x7fffffff)
#define G_MAXUINT32	((guint32) 0xffffffff)

#define G_MININT64	((gint64) G_GINT64_CONSTANT(0x8000000000000000))
#define G_MAXINT64	G_GINT64_CONSTANT(0x7fffffffffffffff)
#define G_MAXUINT64	G_GINT64_CONSTANT(0xffffffffffffffffU)

typedef void* gpointer;
typedef const void *gconstpointer;

typedef gint            (*GCompareFunc)         (gconstpointer  a,
                                                 gconstpointer  b);
typedef gint            (*GCompareDataFunc)     (gconstpointer  a,
                                                 gconstpointer  b,
						 gpointer       user_data);
typedef gboolean        (*GEqualFunc)           (gconstpointer  a,
                                                 gconstpointer  b);
typedef void            (*GDestroyNotify)       (gpointer       data);
typedef void            (*GFunc)                (gpointer       data,
                                                 gpointer       user_data);
typedef guint           (*GHashFunc)            (gconstpointer  key);
typedef void            (*GHFunc)               (gpointer       key,
                                                 gpointer       value,
                                                 gpointer       user_data);
typedef void            (*GFreeFunc)            (gpointer       data);

typedef const gchar *   (*GTranslateFunc)       (const gchar   *str,
						 gpointer       data);

#define G_E     2.7182818284590452353602874713526624977572470937000
#define G_LN2   0.69314718055994530941723212145817656807550013436026
#define G_LN10  2.3025850929940456840179914546843642076011014886288
#define G_PI    3.1415926535897932384626433832795028841971693993751
#define G_PI_2  1.5707963267948966192313216916397514420985846996876
#define G_PI_4  0.78539816339744830961566084581987572104929234984378
#define G_SQRT2 1.4142135623730950488016887242096980785696718753769
#endif
