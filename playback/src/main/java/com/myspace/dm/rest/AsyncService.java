package com.myspace.dm.rest;

import java.io.IOException;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import com.myspace.dm.MovementRepository;
import com.myspace.dm.model.Movement;

@Service
public class AsyncService {
	// parameters
	final static String COMMAND_FMT = "{ \"robotName\": \"%s\", \"cmdString\": \"%s\" }";
	//final static String URL_FMT = "http://%s/command";


	@Value( "${robot.name}" )
	private String robot_name;
	
	@Value( "${api.url}" )
	private String api_url;
	
	@Autowired 
	private MovementRepository movementRepository;
	

    public List<Movement> getMovement(String name) throws Exception  {
    	System.out.println("getMovementByName called.");
    	Iterable<Movement> it = movementRepository.findMovementByName(name);
        if (!it.iterator().hasNext()) {
            throw new Exception("Movements not found for: " + name);
        } else {
            return ( List<Movement>) it;
        }
    }
    
    @Async
    public void replicateMovement(String name) {
    	long lastTime = 0;
    	long delay = 0;
    	List<Movement> list = null;
		try {
			list = getMovement(name);
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			System.out.println("Unable to get the movements from database " + e1.getMessage());
			return;
		}
		if (list == null) {
			
		}
    	for (Movement movement : list) {
    		if (lastTime != 0) {
    			delay = (movement.getTime().longValue() - lastTime);
    			System.out.println("Delay in milliseconds: " + delay);
    		}
    		if (delay > 0) {
        		try {
        			Thread.sleep(delay);
        		}catch(InterruptedException e){ 
        			System.out.println(e);
        		}  
    		}
    		System.out.println("replaying command: " + movement.getCmd() + " to: " + robot_name);
    		try {
				sendCommand(movement.getCmd());
			} catch (JSONException | IOException e) {
				// TODO Auto-generated catch block
				System.out.println("Unable to replay movement: " + e.getMessage());
			}
			lastTime = movement.getTime().longValue();

    	}
    	System.out.println("Finished replaying commands.");
    }
    
	private void sendCommand(String command) throws IOException, JSONException {
		sendCommand(robot_name, command);
	}
	
	private void sendCommand(String robotName, String command) throws IOException, JSONException {
		
		DefaultHttpClient httpClient = new DefaultHttpClient();
		HttpPost postRequest = new HttpPost(api_url);
		StringEntity params =new StringEntity(String.format(COMMAND_FMT, robotName, command));
		postRequest.addHeader("accept", "application/json");
		postRequest.addHeader("content-type", "application/json");
		postRequest.setEntity(params);

		HttpResponse response = httpClient.execute(postRequest);

		if (response.getStatusLine().getStatusCode() != 200 &&
				response.getStatusLine().getStatusCode() != 201) {
			throw new RuntimeException("Failed : HTTP error code : "
			   + response.getStatusLine().getStatusCode());
		}


	}
/*    
	private void sendCommand(String command) throws IOException, JSONException {
		sendCommand(robot_ip, command);
	}
	
	private void sendCommand(String ip, String command) throws IOException, JSONException {
		
		DefaultHttpClient httpClient = new DefaultHttpClient();
		HttpPost postRequest = new HttpPost(String.format("http://%s/rpc/Robot.Cmd", ip));
		StringEntity params =new StringEntity(String.format(COMMAND_FMT, command));
		postRequest.addHeader("accept", "application/json");
		postRequest.addHeader("content-type", "application/json");
		postRequest.setEntity(params);

		HttpResponse response = httpClient.execute(postRequest);

		if (response.getStatusLine().getStatusCode() != 200) {
			throw new RuntimeException("Failed : HTTP error code : "
			   + response.getStatusLine().getStatusCode());
		}


	}
*/
}
