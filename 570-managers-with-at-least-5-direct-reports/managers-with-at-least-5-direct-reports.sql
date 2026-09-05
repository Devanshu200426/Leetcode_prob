# Write your MySQL query statement below
SELECT w1.name 
FROM Employee w1
INNER JOIN Employee w2
ON w1.id=w2.managerId
GROUP BY w2.managerId
HAVING COUNT(w2.managerId)>=5 ;