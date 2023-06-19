#include "shell.h"

/**
 * _realloc - allocate mem and set all values to 0
 * @ptr: pointer to the mem previously allocated (malloc(old_size))
 * @old_size: previous sixe allocated
 * @new_size: new size to reallocate
 * Return: pointer to reallocated mem
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	/* free mem if realloc 0*/
	if (new_size == 0 && ptr != NULL) 
	{
		free(ptr);
		return (NULL);
	}

	/* return ptr if reallocing same old size */
	if (new_size == old_size)
		return (ptr);

	/* mem allocate new size if ptr is null originally */
	if (ptr == NULL) 
	{
		p = malloc(new_size);
		if (p == NULL)
			return (NULL);
		else
			return (p);
	}

	/* mem alloc and chech error */
	p = malloc(new_size); 
	if (p == NULL)
		return (NULL);

	/* fill up values up till min of old or new size */
	for (i = 0; i < old_size && i < new_size; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr); /* free old ptr */

	return (p);
}
