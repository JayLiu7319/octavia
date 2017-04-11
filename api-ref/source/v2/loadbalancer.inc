.. -*- rst -*-

List load balancers
===================

.. rest_method:: GET /v2.0/lbaas/loadbalancers

Lists all load balancers for the project.

Use the ``fields`` query parameter to control which fields are
returned in the response body. Additionally, you can filter results
by using query string parameters. For information, see :ref:`filtering`.

Administrative users can specify a project ID that is different than their own
to list load balancers for other projects.

The list might be empty.

.. rest_status_code:: success ../http-status.yaml

   - 200

.. rest_status_code:: error ../http-status.yaml

   - 400
   - 401
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - fields: fields
   - project_id: project_id_query
   - tenant_id: tenant_id_query

Curl Example
------------

.. literalinclude:: examples/loadbalancers-list-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up
   - created_at: created_at
   - description: description
   - flavor: flavor-id
   - id: loadbalancer-id
   - listeners: listeners
   - loadbalancers: loadbalancers
   - name: name
   - operating_status: operating_status
   - pools: pools_ids
   - project_id: project_id
   - provider: provider
   - provisioning_status: provisioning_status
   - tenant_id: tenant_id
   - vip_address: vip_address
   - vip_network_id: vip_network_id
   - vip_port_id: vip_port_id
   - vip_subnet_id: vip_subnet_id

Response Example
----------------

.. literalinclude:: examples/loadbalancers-list-response.json
   :language: javascript

Create a load balancer
======================

.. rest_method:: POST /v2.0/lbaas/loadbalancers

Creates a load balancer.

This operation provisions a new load balancer by using the
configuration that you define in the request object. After the API
validates the request and starts the provisioning process, the API
returns a response object that contains a unique ID and the status
of provisioning the load balancer.

In the response, the load balancer :ref:`provisioning status<prov_status>` is
``ACTIVE``, ``PENDING_CREATE``, or ``ERROR``.

If the status is ``PENDING_CREATE``, issue GET
``/v2.0/lbaas/loadbalancers/{loadbalancer_id}`` to view the progress of
the provisioning operation. When the load balancer status changes
to ``ACTIVE``, the load balancer is successfully provisioned and
is ready for further configuration.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

Administrative users can specify a project ID that is different than
their own to create load balancers for other projects.

There are three ways to specify a Virtual IP (VIP) network for the load
balancer: provide a ``vip_port_id``, supply a ``vip_subnet_id``, or provide a
``vip_network_id``. Providing a neutron port ID for the ``vip_port_id`` tells
octavia to use this port for the VIP. Some port settings may be changed or
removed as required by octavia, but the IP address will be retained.
Specifying a neutron subnet ID will tell octavia to create a neutron port
on this subnet and allocate an IP address from the subnet if the
``vip_address`` was not specified. If ``vip_address`` was specified, octavia
will attempt to allocate the ``vip_address`` from the subnet for the VIP
address. Finally, when a ``vip_network_ip`` is specified octavia will select
a subnet from the network, preferring IPv4 over IPv6 subnets.

An optional ``flavor`` attribute can be used to create the load balancer
using a pre-configured octavia flavor.  Flavors are created by the operator
to allow custom load balancer configurations, such as allocating more
memory for the load balancer.

You can also specify the ``provider`` attribute when you create a
load balancer. The ``provider`` attribute specifies which backend should
be used to create the load balancer.  This could be the default provider
(``octavia``) or a vendor supplied ``provider`` if one has been installed.
Setting both a flavor and a provider will result in a conflict error.

.. rest_status_code:: success ../http-status.yaml

   - 201

.. rest_status_code:: error ../http-status.yaml

   - 400
   - 401
   - 403
   - 404
   - 500
   - 503

Request
-------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up-default-optional
   - description: description-optional
   - flavor: flavor-id-optional
   - listeners: listeners-optional
   - loadbalancer: loadbalancer
   - name: name-optional
   - project_id: project_id-optional
   - provider: provider-optional
   - tenant_id: tenant_id
   - vip_address: vip_address-optional
   - vip_network_id: vip_network_id-optional
   - vip_port_id: vip_port_id-optional
   - vip_subnet_id: vip_subnet_id-optional

Request Example
----------------

.. literalinclude:: examples/loadbalancer-create-request.json
   :language: javascript

Curl Example
------------

.. literalinclude:: examples/loadbalancer-create-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up
   - created_at: created_at
   - description: description
   - flavor: flavor-id
   - id: loadbalancer-id
   - listeners: listeners
   - loadbalancer: loadbalancer
   - name: name
   - operating_status: operating_status
   - pools: pools_ids
   - project_id: project_id
   - provider: provider
   - provisioning_status: provisioning_status
   - tenant_id: tenant_id
   - vip_address: vip_address
   - vip_network_id: vip_network_id
   - vip_port_id: vip_port_id
   - vip_subnet_id: vip_subnet_id

Response Example
----------------

.. literalinclude:: examples/loadbalancer-create-response.json
   :language: javascript

Creating a Fully Populated Load Balancer
----------------------------------------

You can configure all documented features of the load balancer at
creation time by specifying the additional elements or attributes
in the request.

Request Example
---------------

.. literalinclude:: examples/loadbalancer-full-create-request.json
   :language: javascript

Response Example
----------------

.. literalinclude:: examples/loadbalancer-full-create-response.json
   :language: javascript

Show load balancer details
==========================

.. rest_method:: GET /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Shows the details of a load balancer.

If you are not an administrative user and the load balancer object does not
belong to your project, the service returns the HTTP ``Forbidden (403)``
response code.

This operation does not require a request body.

.. rest_status_code:: success ../http-status.yaml

   - 200

.. rest_status_code:: error ../http-status.yaml

   - 401
   - 403
   - 404
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - loadbalancer_id: path-loadbalancer-id

Curl Example
------------

.. literalinclude:: examples/loadbalancer-show-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up
   - created_at: created_at
   - description: description
   - flavor: flavor-id
   - id: loadbalancer-id
   - loadbalancer: loadbalancer
   - listeners: listeners
   - name: name
   - operating_status: operating_status
   - pools: pools_ids
   - project_id: project_id
   - provider: provider
   - provisioning_status: provisioning_status
   - tenant_id: tenant_id
   - vip_address: vip_address
   - vip_network_id: vip_network_id
   - vip_port_id: vip_port_id
   - vip_subnet_id: vip_subnet_id

Response Example
----------------

.. literalinclude:: examples/loadbalancer-show-response.json
   :language: javascript

Update a load balancer
======================

.. rest_method:: PUT /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Updates a load balancer.

If the request is valid, the service returns the ``Accepted (202)``
response code. To confirm the update, check that the load balancer
provisioning status is ``ACTIVE``. If the status is
``PENDING_UPDATE``, use a GET operation to poll the load balancer
object for changes.

This operation returns the updated load balancer object with the
``ACTIVE``, ``PENDING_UPDATE``, or ``ERROR`` provisioning status.

.. rest_status_code:: success ../http-status.yaml

   - 202

.. rest_status_code:: error ../http-status.yaml

   - 400
   - 401
   - 403
   - 404
   - 409
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up-optional
   - description: description-optional
   - loadbalancer: loadbalancer
   - loadbalancer_id: path-loadbalancer-id
   - name: name-optional

Request Example
---------------

.. literalinclude:: examples/loadbalancer-update-request.json
   :language: javascript

Curl Example
------------

.. literalinclude:: examples/loadbalancer-update-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - admin_state_up: admin_state_up
   - created_at: created_at
   - description: description
   - flavor: flavor-id
   - id: loadbalancer-id
   - listeners: listeners
   - loadbalancer: loadbalancer
   - name: name
   - operating_status: operating_status
   - pools: pools_ids
   - project_id: project_id
   - provider: provider
   - provisioning_status: provisioning_status
   - tenant_id: tenant_id
   - vip_address: vip_address
   - vip_network_id: vip_network_id
   - vip_port_id: vip_port_id
   - vip_subnet_id: vip_subnet_id

Response Example
----------------

.. literalinclude:: examples/loadbalancer-update-response.json
   :language: javascript

Remove a load balancer
======================

.. rest_method:: DELETE /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Removes a load balancer and its associated configuration from the project.

The API immediately purges any and all configuration data, depending on the
configuration settings.. You cannot recover it.

.. rest_status_code:: success ../http-status.yaml

   - 204

.. rest_status_code:: error ../http-status.yaml

   - 400
   - 401
   - 403
   - 404
   - 409
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - loadbalancer_id: path-loadbalancer-id

Curl Example
------------

.. literalinclude:: examples/loadbalancer-delete-curl
   :language: bash

Response
--------

There is no body content for the response of a successful DELETE request.

Get load balancer statistics
============================

.. rest_method:: GET /v2.0/lbaas/loadbalancers/{loadbalancer_id}/stats

Shows the current statistics for a load balancer.

This operation returns the statistics of a load balancer object identified
by loadbalancer_id.

If you are not an administrative user and the load balancer object does not
belong to your project, the service returns the HTTP ``Forbidden (403)``
response code.

This operation does not require a request body.

.. rest_status_code:: success ../http-status.yaml

   - 200

.. rest_status_code:: error ../http-status.yaml

   - 401
   - 403
   - 404
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - loadbalancer_id: path-loadbalancer-id

Curl Example
------------

.. literalinclude:: examples/loadbalancer-stats-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - stats: stats
   - active_connections: active_connections
   - bytes_in: bytes_in
   - bytes_out: bytes_out
   - request_errors: request_errors
   - total_connections: total_connections

Response Example
----------------

.. literalinclude:: examples/loadbalancer-stats-response.json
   :language: javascript

Get the load balancer status tree
=================================

.. rest_method:: GET /v2.0/lbaas/loadbalancers/{loadbalancer_id}/status

Shows the status tree for a load balancer.

This operation returns a status tree for a load balancer object, by load
balancer ID.

``provisioning_status`` is the status associated with lifecycle of the resource.
See :ref:`prov_status` for descriptions of the status codes.

``operating_status`` is the observed status of the resource.
See :ref:`op_status` for descriptions of the status codes.

If you are not an administrative user and the load balancer object does not
belong to your project, the service returns the HTTP ``Forbidden (403)``
response code.

If the operation succeeds, the returned element is a status tree that contains
the load balancer and all provisioning and operating statuses for its children.

.. rest_status_code:: success ../http-status.yaml

   - 200

.. rest_status_code:: error ../http-status.yaml

   - 401
   - 403
   - 404
   - 500

Request
-------

.. rest_parameters:: ../parameters.yaml

   - loadbalancer_id: path-loadbalancer-id

Curl Example
------------

.. literalinclude:: examples/loadbalancer-status-curl
   :language: bash

Response Parameters
-------------------

.. rest_parameters:: ../parameters.yaml

   - action: action
   - address: address
   - healthmonitor: healthmonitor-status
   - id: id
   - l7policies: l7policies-status-object-list
   - l7rules: l7rules-status-object-list
   - listeners: listeners-status-object-list
   - loadbalancer: loadbalancer-status
   - members: members-status-object-list
   - name: name
   - operating_status: operating_status
   - pools: pools-status-list
   - protocol_port: protocol_port
   - provisioning_status: provisioning_status
   - statuses: statuses
   - type: type

Response Example
----------------

.. literalinclude:: examples/loadbalancer-status-response.json
   :language: javascript