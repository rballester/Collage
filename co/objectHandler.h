
/* Copyright (c) 2012-2013, Stefan Eilemann <eile@eyescale.ch>
 *
 * This file is part of Collage <https://github.com/Eyescale/Collage>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CO_OBJECTHANDLER_H
#define CO_OBJECTHANDLER_H

#include <co/api.h>
#include <co/types.h>

namespace co
{
    /** Interface for entities which map and register objects. */
    class ObjectHandler
    {
    public:
        /**
         * Register a distributed object.
         *
         * Registering a distributed object makes this object the master
         * version. The object's identifier is used to map slave instances of
         * the object. Master versions of objects are typically writable and can
         * commit new versions of the distributed object.
         *
         * @param object the object instance.
         * @return true if the object was registered, false otherwise.
         * @version 1.0
         */
        virtual bool registerObject( Object* object ) = 0;

        /**
         * Deregister a distributed object.
         *
         * @param object the object instance.
         * @version 1.0
         */
        virtual void deregisterObject( Object* object ) = 0;

        /**
         * Start mapping a distributed object.
         *
         * @param object the object to map.
         * @param id the object identifier
         * @param version the version to map.
         * @param master the master node, may be invalid/0.
         * @return the request identifier for mapObjectSync().
         * @version 1.0
         */
        virtual uint32_t mapObjectNB( Object* object, const UUID& id,
                                      const uint128_t& version,
                                      NodePtr master ) = 0;

        /** Finalize the mapping of a distributed object. @version 1.0 */
        virtual bool mapObjectSync( const uint32_t requestID ) = 0;

        /** Unmap a mapped object. @version 1.0 */
        virtual void unmapObject( Object* object ) = 0;

        /** Convenience method to deregister or unmap an object. @version 1.0 */
        CO_API void releaseObject( Object* object );

    protected:
        /** Construct a new object handler. @version 1.0 */
        ObjectHandler() {}

        /** Destroy this object handler. @version 1.0 */
        virtual ~ObjectHandler() {}
    };
}
#endif // CO_OBJECTHANDLER_H
