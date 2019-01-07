/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (https://icinga.com/)           *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "icinga/checkable.hpp"
#include "base/configobject.hpp"
#include "base/dictionary.hpp"
#include "base/function.hpp"
#include "base/functionwrapper.hpp"
#include "base/scriptframe.hpp"

using namespace icinga;

static void CheckableProcessCheckResult(const CheckResult::Ptr& cr)
{
	ScriptFrame *vframe = ScriptFrame::GetCurrentFrame();
	Checkable::Ptr self = vframe->Self;
	REQUIRE_NOT_NULL(self);
	self->ProcessCheckResult(cr);
}

Object::Ptr Checkable::GetPrototype()
{
	static Dictionary::Ptr prototype = new Dictionary({
		{ "process_check_result", new Function("Checkable#process_check_result", CheckableProcessCheckResult, { "cr" }, false) }
	});

	return prototype;
}

