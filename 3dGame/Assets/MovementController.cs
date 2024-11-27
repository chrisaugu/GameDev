using System;
using UnityEngine;

public class MovementController : MonoBehaviour
{
	public float movementSpeed = 3.0f;
	private Rigidbody rd;

	Vector3 movement;

	private void Start()
	{
		rd = GetComponent<Rigidbody>();
	}

	private void Update()
	{

	}

	void FixedUpdate()
	{
		movement.x = Input.GetAxisRaw("Horizontal");
		movement.y = Input.GetAxisRaw("Vertical");

		movement.Normalize();

	}
}
