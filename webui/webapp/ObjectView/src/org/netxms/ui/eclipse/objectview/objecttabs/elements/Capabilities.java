/**
 * NetXMS - open source network management system
 * Copyright (C) 2003-2011 Victor Kirhenshtein
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
package org.netxms.ui.eclipse.objectview.objecttabs.elements;

import org.eclipse.swt.widgets.Composite;
import org.netxms.client.objects.GenericObject;
import org.netxms.client.objects.Node;

/**
 * "Capabilities" element for object overview page
 *
 */
public class Capabilities extends TableElement
{
	private static final long serialVersionUID = 1L;

	/**
	 * @param parent
	 * @param object
	 */
	public Capabilities(Composite parent, GenericObject object)
	{
		super(parent, object);
	}

	/* (non-Javadoc)
	 * @see org.netxms.ui.eclipse.objectview.objecttabs.elements.OverviewPageElement#getTitle()
	 */
	@Override
	protected String getTitle()
	{
		return "Capabilities";
	}

	/* (non-Javadoc)
	 * @see org.netxms.ui.eclipse.objectview.objecttabs.elements.TableElement#fillTable()
	 */
	@Override
	protected void fillTable()
	{
		if (!(getObject() instanceof Node))
			return;
		
		Node node = (Node)getObject();
		addFlag("isAgent", (node.getFlags() & Node.NF_IS_NATIVE_AGENT) != 0);
		addFlag("isBridge", (node.getFlags() & Node.NF_IS_BRIDGE) != 0);
		addFlag("isCDP", (node.getFlags() & Node.NF_IS_CDP) != 0);
		addFlag("isDot1x", (node.getFlags() & Node.NF_IS_8021X) != 0);
		addFlag("isLLDP", (node.getFlags() & Node.NF_IS_LLDP) != 0);
		addFlag("isNDP", (node.getFlags() & Node.NF_IS_SONMP) != 0);
		addFlag("isPrinter", (node.getFlags() & Node.NF_IS_PRINTER) != 0);
		addFlag("isRouter", (node.getFlags() & Node.NF_IS_ROUTER) != 0);
		addFlag("isSNMP", (node.getFlags() & Node.NF_IS_SNMP) != 0);
		addFlag("isSTP", (node.getFlags() & Node.NF_IS_STP) != 0);
		addFlag("isVRRP", (node.getFlags() & Node.NF_IS_VRRP) != 0);
		if ((node.getFlags() & Node.NF_IS_SNMP) != 0)
		{
			addPair("snmpPort", Integer.toString(node.getSnmpPort()));
			addPair("snmpVersion", getSnmpVersionName(node.getSnmpVersion()));
		}
	}
	
	/**
	 * Add flag to list
	 * 
	 * @param name
	 * @param value
	 */
	private void addFlag(String name, boolean value)
	{
		addPair(name, value ? "Yes" : "No");
	}
	
	/**
	 * Get SNMP version name from internal number
	 * 
	 * @param version
	 * @return
	 */
	private String getSnmpVersionName(int version)
	{
		switch(version)
		{
			case Node.SNMP_VERSION_1:
				return "1";
			case Node.SNMP_VERSION_2C:
				return "2c";
			case Node.SNMP_VERSION_3:
				return "3";
			default:
				return "???";
		}
	}

	/* (non-Javadoc)
	 * @see org.netxms.ui.eclipse.objectview.objecttabs.elements.OverviewPageElement#isApplicableForObject(org.netxms.client.objects.GenericObject)
	 */
	@Override
	public boolean isApplicableForObject(GenericObject object)
	{
		return object instanceof Node;
	}
}
