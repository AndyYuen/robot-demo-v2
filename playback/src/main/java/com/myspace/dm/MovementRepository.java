package com.myspace.dm;



import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.concurrent.CompletableFuture;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import com.myspace.dm.model.Movement;

@Repository
public class MovementRepository {
	private final String MOVEMENT_QUERY = "select * from movement where name=? order by mtime asc";
	
	@Autowired 
	private JdbcTemplate jdbcTemplate;
 
 

    public List<Movement> findMovementByName(String name) {
        return jdbcTemplate.query(MOVEMENT_QUERY, 
        		new Object[]{name}, new MovementRowMapper());
    }

 
class MovementRowMapper implements RowMapper<Movement>
{
    @Override
    public Movement mapRow(ResultSet rs, int rowNum) throws SQLException {
        Movement movement = new Movement();
        movement.setId(rs.getLong("id"));
        movement.setName(rs.getString("name"));
        movement.setTime(new Long(rs.getString("mtime"))); 
        movement.setCmd(rs.getNString("cmd"));
        return movement;
    }
}

}
