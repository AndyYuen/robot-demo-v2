package com.myspace.dm;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.scheduling.annotation.EnableAsync;


@SpringBootApplication
@EnableAsync
//@ComponentScan(basePackageClasses = CustomerEndpoint.class)
public class ServiceApplication {

    public static void main(String[] args) {
    	SpringApplication.run(ServiceApplication.class, args);
    }

}
