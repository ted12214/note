```SQL

-- 输出调试信息
DELIMITER $$

DROP PROCEDURE IF EXISTS debug_msg $$
CREATE PROCEDURE debug_msg(enabled INTEGER, msg VARCHAR(255))
BEGIN
  IF enabled THEN 
    select concat("** ", msg) AS '** DEBUG:';
END IF;

   END $$

DELIMITER ;

-- 来看统计充值金额和充值人数

DELIMITER $$

DROP PROCEDURE IF EXISTS LAIKAN_C1$$

CREATE PROCEDURE  LAIKAN_C1 
    (IN u_create_time date   -- 用户创建时间
      , IN t_create_time date    -- 充值时间开始时间
      )
   BEGIN
        DECLARE t_create_time_end date;   -- 充值时间截止日期
        DECLARE u_create_time_end date;   -- 用户创建时间截止日期
        DECLARE ucount NUMERIC;   -- 用户计数
        DECLARE mcount NUMERIC;   -- 充值计数
        DECLARE en NUMERIC DEFAULT 1; -- 输出信息标志位

        SET u_create_time_end = u_create_time;

        SELECT date_add(last_day(t_create_time), INTERVAL 1 DAY) INTO t_create_time_end;
        
        -- 循环判断当前用户创建时间 小于 充值开始时间节点
        WHILE u_create_time <= t_create_time DO
          -- 设置用户创建截止时间
          SELECT date_add(last_day(u_create_time), INTERVAL 1 DAY) INTO u_create_time_end;

          SELECT  count(distinct(u.id)) ,sum(t.real_money) INTO ucount,mcount
          FROM legion_accounts_user u, wings_money_topup t
          where u.id = t.user_id and u.status = 0 and u.email LIKE '%lk.motie'
          AND u.create_time >= u_create_time
          AND u.create_time < u_create_time_end
          AND t.create_time >= t_create_time
          AND t.create_time < t_create_time_end
          AND t.real_money > 0
          AND t.update_time is not null and t.update_time > '1970-01-01 08:00:00';
          
          -- 输出调试信息
          call debug_msg(en, CONCAT(ucount,' , ',mcount));
          -- 重置用户创建时间
          SET u_create_time = u_create_time_end;
          
          END WHILE;

   END $$

DELIMITER ;
```
