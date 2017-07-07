/**
 * NetXMS - open source network management system
 * Copyright (C) 2003-2012 Victor Kirhenshtein
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
package org.netxms.client.objects;

import java.util.Date;
import java.util.Set;
import org.netxms.base.Logger;
import org.netxms.base.NXCPCodes;
import org.netxms.base.NXCPMessage;
import org.netxms.client.MacAddress;
import org.netxms.client.NXCSession;
import org.netxms.client.sensor.configs.DlmsConfig;
import org.netxms.client.sensor.configs.LoraWanConfig;
import org.netxms.client.sensor.configs.SensorConfig;

/**
 * Mobile device object
 */
public class Sensor extends DataCollectionTarget
{
   /**
    * Sensor flags
    */
   public final static int SENSOR_ACTIVE = 1;
   
   /**
    * Sensor communication protocol type
    */
   public final static int  SENSOR_PROTO_UNKNOWN = 0;
   public final static int  COMM_LORAWAN = 1;
   public final static int  COMM_DLMS = 2;
   
   public final static String[] COMM_METHOD = { "Unknown", "LoRaWAN", "DLMS"};
   
   /**
    * Sensor device class
    */
   public final static int  SENSOR_CLASS_UNKNOWN = 0;
   public final static int  SENSOR_UPS = 1;
   public final static int  SENSOR_WATER_METER = 2;
   public final static int  SENSOR_ELECTR_METER = 3;
   
   public final static String[] DEV_CLASS_NAMES = { "Unknown", "UPS", "Water meter", "Electricity meter" };
   
   
   private int flags;
   protected MacAddress macAddress;
	private int deviceClass;
	private String vendor;
	private int  commProtocol;
	private SensorConfig config;
	private String serialNumber;
	private String deviceAddress;
	private String metaType;
	private String description;
	private Date lastConnectionTime;
	private int frameCount; //zero when no info
   private int signalStrenght; //+1 when no information(cannot be +)
   private int signalNoise; //*10 from origin number
   private int frequency; //*10 from origin number
   private long proxyId;
	
	/**
	 * Object constructor from message
	 * 
	 * @param msg
	 * @param session
	 */
	public Sensor(NXCPMessage msg, NXCSession session)
	{
		super(msg, session);
		flags = msg.getFieldAsInt32(NXCPCodes.VID_SENSOR_FLAGS);
		macAddress = new MacAddress(msg.getFieldAsBinary(NXCPCodes.VID_MAC_ADDR));
	   deviceClass  = msg.getFieldAsInt32(NXCPCodes.VID_DEVICE_CLASS);
	   vendor = msg.getFieldAsString(NXCPCodes.VID_VENDOR);
	   commProtocol = msg.getFieldAsInt32(NXCPCodes.VID_COMM_PROTOCOL);
	   setXmlConfig(msg.getFieldAsString(NXCPCodes.VID_XML_CONFIG));
	   serialNumber = msg.getFieldAsString(NXCPCodes.VID_SERIAL_NUMBER);
	   deviceAddress = msg.getFieldAsString(NXCPCodes.VID_DEVICE_ADDRESS);
	   metaType = msg.getFieldAsString(NXCPCodes.VID_META_TYPE);
	   description = msg.getFieldAsString(NXCPCodes.VID_DESCRIPTION);
	   lastConnectionTime  = msg.getFieldAsDate(NXCPCodes.VID_LAST_CONN_TIME);
	   frameCount = msg.getFieldAsInt32(NXCPCodes.VID_FRAME_COUNT); 
	   signalStrenght = msg.getFieldAsInt32(NXCPCodes.VID_SIGNAL_STRENGHT); 
	   signalNoise = msg.getFieldAsInt32(NXCPCodes.VID_SIGNAL_NOISE); 
	   frequency = msg.getFieldAsInt32(NXCPCodes.VID_FREQUENCY);
	   proxyId = msg.getFieldAsInt32(NXCPCodes.VID_SENSOR_PROXY);
	}

	/* (non-Javadoc)
	 * @see org.netxms.client.objects.AbstractObject#isAllowedOnMap()
	 */
	@Override
	public boolean isAllowedOnMap()
	{
		return true;
	}

   /* (non-Javadoc)
    * @see org.netxms.client.objects.AbstractObject#isAlarmsVisible()
    */
   @Override
   public boolean isAlarmsVisible()
   {
      return true;
   }

	/**
	 * @return the vendor
	 */
	public final String getVendor()
	{
		return vendor;
	}
	/**
	 * @return the serialNumber
	 */
	public final String getSerialNumber()
	{
		return serialNumber;
	}

	/* (non-Javadoc)
	 * @see org.netxms.client.objects.GenericObject#getObjectClassName()
	 */
	@Override
	public String getObjectClassName()
	{
		return "Sensor";
	}

   /* (non-Javadoc)
    * @see org.netxms.client.objects.AbstractObject#getStrings()
    */
   @Override
   public Set<String> getStrings()
   {      
      Set<String> strings = super.getStrings();
      addString(strings, macAddress.toString());
      //addString(strings, DEV_CLASS_NAMES[deviceClass]);
      addString(strings, vendor);
      addString(strings, serialNumber);
      addString(strings, deviceAddress);
      addString(strings, metaType);
      addString(strings, description);
      return strings;
   }

   /**
    * @return the flags
    */
   public int getFlags()
   {
      return flags;
   }

   /**
    * @return the macAddress
    */
   public MacAddress getMacAddress()
   {
      return macAddress;
   }

   /**
    * @return the frameCount
    */
   public int getFrameCount()
   {
      return frameCount;
   }

   /**
    * @return the signalStrenght
    */
   public int getSignalStrenght()
   {
      return signalStrenght;
   }

   /**
    * @return the frequency
    */
   public int getFrequency()
   {
      return frequency;
   }

   /**
    * @return the deviceClass
    */
   public int getDeviceClass()
   {
      return deviceClass;
   }

   /**
    * @return the commProtocol
    */
   public int getCommProtocol()
   {
      return commProtocol;
   }

   /**
    * @return the xmlConfig
    */
   public String getXmlConfig()
   {
      try
      {
         return config.createXml();
      }
      catch(Exception e)
      {
         return "";
      }
   }
   
   /**
    *  Config class creator from XML 
    *  
    * @param xml xml for object creation
    */
   private void setXmlConfig(String xml)
   {
      switch(commProtocol)
      {
         case COMM_LORAWAN:
            try
            {
               config = SensorConfig.createFromXml(LoraWanConfig.class, xml);
            }
            catch(Exception e)
            {
               config = new LoraWanConfig();
               Logger.debug("Sensor.Sensor", "Cannot parse LoraWanConfig XML", e);
            }
            break;
         case COMM_DLMS:
            try
            {
               config = SensorConfig.createFromXml(DlmsConfig.class, xml);
            }
            catch(Exception e)
            {
               config = new DlmsConfig();
               Logger.debug("Sensor.Sensor", "Cannot parse DlmsConfig XML", e);
            }        
            break;
         default:
            config = null;
      }
   }

   /**
    * @return the deviceAddress
    */
   public String getDeviceAddress()
   {
      return deviceAddress;
   }

   /**
    * @return the metaType
    */
   public String getMetaType()
   {
      return metaType;
   }

   /**
    * @return the description
    */
   public String getDescription()
   {
      return description;
   }

   /**
    * @return the lastConnectionTime
    */
   public Date getLastConnectionTime()
   {
      return lastConnectionTime;
   }

   /**
    * @return the proxyId
    */
   public long getProxyId()
   {
      return proxyId;
   }

   /**
    * @return the signalNoise
    */
   public int getSignalNoise()
   {
      return signalNoise;
   }
}
