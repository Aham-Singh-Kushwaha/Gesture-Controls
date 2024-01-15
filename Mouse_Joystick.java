import com.fazecast.jSerialComm.*;
import java.awt.event.*;
import java.awt.Robot;
import java.awt.MouseInfo; 
import java.lang.Thread;
public class Mouse_Joystick
{
    public static void main (String[] Args)
    {

        int BaudRate = 9600;
        int DataBits = 8;
        int StopBits = SerialPort.ONE_STOP_BIT;
        int Parity   = SerialPort.NO_PARITY;

        SerialPort [] AvailablePorts = SerialPort.getCommPorts();

        System.out.println("\n\n SerialPort Data Reception");

        System.out.print("\n\n Available Ports ");
        for (int i = 0; i<AvailablePorts.length ; i++)
        {
            System.out.println(i + " - " + AvailablePorts[i].getSystemPortName() + " -> " + AvailablePorts[i].getDescriptivePortName());
        }

        SerialPort MySerialPort = AvailablePorts[0];

        MySerialPort.setComPortParameters(BaudRate,DataBits,StopBits,Parity);

        MySerialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 1000, 0); 

        MySerialPort.openPort(); 
        if (MySerialPort.isOpen())
            System.out.println("\n" + MySerialPort.getSystemPortName() + " is Open ");
        else
            System.out.println(" Port not open ");

        System.out.println("\n Selected Port               = " + MySerialPort.getSystemPortName());
        System.out.println(" Selected Baud rate          = " + MySerialPort.getBaudRate());
        System.out.println(" Selected Number of DataBits = " + MySerialPort.getNumDataBits());
        System.out.println(" Selected Number of StopBits = " + MySerialPort.getNumStopBits());
        System.out.println(" Selected Parity             = " + MySerialPort.getParity());
        System.out.println(" Selected Read Time Out      = " + MySerialPort.getReadTimeout() + "mS");

        MySerialPort.flushIOBuffers();

        try 
        {Thread.sleep(3000);
            byte[] WriteBytes= new byte[1];
            WriteBytes[0]='a';
            MySerialPort.writeBytes(WriteBytes,1);
            while (true)
            {
                byte[] readBuffer = new byte[15];
                int numRead = MySerialPort.readBytes(readBuffer, readBuffer.length);
                System.out.print("Read " + numRead + " bytes -");
                String S = new String(readBuffer, "UTF-8").trim(); 
                System.out.println("Received -> "+ S);
                int x =Integer.parseInt(S.substring(S.indexOf(',')+1,S.indexOf(' ')));
                int y =Integer.parseInt(S.substring(S.indexOf(' ')+1,S.indexOf('.')));
                int sw =Integer.parseInt(S.substring(S.indexOf('.')+1,S.indexOf('|')));
                Robot bot = null;
                bot = new Robot();
                //int mask = InputEvent.BUTTON1_DOWN_MASK;
                //int mask1 = InputEvent.BUTTON3_DOWN_MASK;
                int mouseY = MouseInfo.getPointerInfo().getLocation().y;
                int mouseX = MouseInfo.getPointerInfo().getLocation().x;
                if (Math.abs(x - 500) > 5)
                    mouseX = mouseX + (int)((500 - x) * 0.1);
                if (Math.abs(y - 500) > 5)
                    mouseY = mouseY - (int)((500 - y) * 0.1);
                bot.mouseMove(mouseX,mouseY);
                if(sw==1)
                {
                    bot.keyPress(KeyEvent.VK_W);
                    
                }
                
                else if(sw==2)
                {
                    bot.keyPress(KeyEvent.VK_S);
                    
                }
                
                else if(sw==3)
                {
                    bot.keyPress(KeyEvent.VK_SPACE);
                    
                }
                
                else if(sw==0)
                {
                    bot.keyRelease(KeyEvent.VK_W);
                    bot.keyRelease(KeyEvent.VK_S);
                    bot.keyRelease(KeyEvent.VK_SPACE);
                }
            }
        }

        catch (Exception e) 
        {
            e.printStackTrace(); 
        }

        MySerialPort.closePort();
        if (MySerialPort.isOpen())
            System.out.println(MySerialPort.getSystemPortName() + " is Open ");
        else
            System.out.println("\n Port not open ");

    }
}