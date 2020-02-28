package com.myspace.dm.rest;


import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import com.myspace.dm.MovementRepository;
import com.myspace.dm.model.Movement;

@RestController
//@CrossOrigin(origins = "http://localhost:4200")
public class ServiceController {

	@Autowired 
	private AsyncService service;

    @GetMapping("/movement/{name}")
    public List<Movement> getMovementByName(@PathVariable String name) throws Exception  {
    	System.out.println("getMovementByName called.");
    	return service.getMovement(name);
    }

    @GetMapping("/replicate/{name}")
    public void replicateMovementByName(@PathVariable String name) throws Exception  {
    	System.out.println("replicateMovementByName called.");
    	service.replicateMovement(name);
    }

}
