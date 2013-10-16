/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voß <thomas.voss@canonical.com>
 */
#ifndef DBUS_ORG_FREEDESKTOP_DBUS_PROPERTY_H_
#define DBUS_ORG_FREEDESKTOP_DBUS_PROPERTY_H_

#include <memory>

namespace org
{
namespace freedesktop
{
namespace dbus
{
class Object;

template<typename PropertyType>
class Property
{
public:
    const typename PropertyType::ValueType& value();
    void value(const typename PropertyType::ValueType& new_value);

    bool is_writable() const;
protected:
    friend class Object;

    static std::shared_ptr<Property<PropertyType>> make_property(
        const std::shared_ptr<Object>& parent);

private:
    Property(
        const std::shared_ptr<Object>& parent,
        const std::string& interface,
        const std::string& name,
        bool writable);

    void handle_get(DBusMessage* msg);
    void handle_set(DBusMessage* msg);

    std::shared_ptr<Object> parent;
    std::string interface;
    std::string name;
    bool writable;

    types::Variant<typename PropertyType::ValueType> property_value;
};
}
}
}

#include "impl/property.h"

#endif // DBUS_ORG_FREEDESKTOP_DBUS_PROPERTY_H_
