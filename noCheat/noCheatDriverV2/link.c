/************************************************************************/
/* Link Functions                                                       */
/*   Handle link initiation and verification                            */
/************************************************************************/

// Include DDK
#include <ntddk.h>

// Include driver headers
#include "defines.h"
#include "ncDriverDefines.h"
#include "structures.h"
#include "globals.h"

/*
 * Verifies a link when the service connects.
 *	Various security, version, and sizing/alignment
 *	checks are performed here.
 */
char VerifyLink(struct NC_CONNECT_INFO_INPUT* ncRInf)
{
	// Check security
	if(ncRInf->iSecurityCode != NC_LINK_SEC_CODE)
	{
		// Log and break
		LOG2("Link security code failed! (%X)", ncRInf->iSecurityCode);
		return 0;
	}else
		LOG2("Link passed security check");

	// Verify version
	if(ncRInf->iDSLinkVersion > NC_DS_LINK_VERSION)
	{
		// Log and break
		LOG2("Service of link is newer than driver! (%d > %d)", ncRInf->iDSLinkVersion, NC_DS_LINK_VERSION);
		return 0;
	}else if(ncRInf->iDSLinkVersion < NC_DS_LINK_VERSION) {
		// Log and break
		LOG2("Driver of link is newer than service of link! (%d < %d)", ncRInf->iDSLinkVersion, NC_DS_LINK_VERSION);
		return 0;
	}

	// Log
	LOG2("Verified link version");

	// Return true
	return 1;
}

/*
 * Tries to map a link
 */
VOID TryMapLink(void* src, struct TEMP_MAP_PARAMS* dest, struct NC_CONNECT_INFO_OUTPUT* returnInf, int aSize, SIZE_T size)
{
	// Check size
	NASSERT((aSize == size), {returnInf->bSizeMismatch = 1; return;});

	// Attempt to map space
	dest->oContainer = (void*)MmMapIoSpace(MmGetPhysicalAddress(src), size, 0);

	// Check for null
	if(dest->oContainer == NULL)
	{
		LOG3("Could not map IO space!");
		return;
	}

	// Set parameters
	dest->bMapped = 1;
	dest->iSize = size;
}

/*
 * Nullifies all links
 */
VOID CloseLinks()
{
	// Setup vars
	struct TEMP_MAP_PARAMS* p;
	int total, i;

	// Calculate total
	total = sizeof(sSpaces) / sizeof(struct TEMP_MAP_PARAMS);

	// Create feux pointer
	p = (struct TEMP_MAP_PARAMS*)&sSpaces;

	// Iterate through the table and turn off the Mapped flags
	for(i = 0; i < total; i++)
	{
		// If it's mapped...
		if(p[i].bMapped == 1)
		{
			// Unmap it
			MmUnmapIoSpace(p[i].oContainer, (SIZE_T)p[i].iSize);

			// Mark that it's unmapped
			p[i].bMapped = 0;
		}
	}
}