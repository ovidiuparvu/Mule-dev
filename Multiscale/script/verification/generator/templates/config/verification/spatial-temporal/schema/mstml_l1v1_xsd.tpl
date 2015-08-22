<?xml version="1.0" encoding="utf-8"?>

<!-- 
/*{% for line in auto_generated_warning %}*/
    /*{{ line }}*/
/*{% endfor %}*/
-->

<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">

    <!-- Human-readable information -->
    
    <xs:annotation>
        <xs:documentation xml:lang="en">
            Multiscale Spatial Temporal Markup Language description.
            Copyright 2015 Ovidiu Parvu. 
        </xs:documentation>
    </xs:annotation>

    <!-- Elements -->
    
    <xs:element name="experiment" type="ExperimentType"/>
    
    <!-- User-defined complex types -->
    
    <xs:complexType name="ExperimentType">
        <xs:sequence>
            <xs:element minOccurs="1" maxOccurs="unbounded" name="timepoint" type="TimepointType" >
                <!-- Uniqueness constraints -->
                
                <xs:unique name="UniqueNumericStateVariables">
                    <xs:selector xpath="numericStateVariable"/>
                    <xs:field xpath="@scaleAndSubsystem"/>            
                    <xs:field xpath="name"/>
                </xs:unique>
                
                <xs:unique name="UniqueSpatialEntities">
                    <xs:selector xpath="spatialEntity"/>
                    <xs:field xpath="@spatialType"/>
                    <xs:field xpath="@scaleAndSubsystem"/>
                    /*{% for spatial_measure in spatial_measures %}*/
                    <xs:field xpath="/*{{ spatial_measure.name }}*/"/>
                    /*{% endfor %}*/
                </xs:unique> 
            </xs:element>
        </xs:sequence>
    </xs:complexType>

    <xs:complexType name="TimepointType">
        <xs:sequence>
            <xs:element minOccurs="0" maxOccurs="unbounded" name="spatialEntity" type="SpatialEntityType"/>
            <xs:element minOccurs="0" maxOccurs="unbounded" name="numericStateVariable" type="NumericStateVariableType"/>
        </xs:sequence>
        
        <xs:attribute name="value" type="NonNegativeDoubleType"/>
    </xs:complexType>

    <xs:complexType name="SpatialEntityType">
        <xs:all>
        /*{% for spatial_measure in spatial_measures %}*/
            <xs:element name="/*{{ spatial_measure.name }}*/" type="/*{{ spatial_measure.name|first_to_upper }}*/Type"/>
        /*{% endfor %}*/
        </xs:all>
        
        <xs:attribute name="spatialType" type="SpatialMetaType" use="required"/>
        <xs:attribute name="scaleAndSubsystem" type="ScaleAndSubsystemType"/>
    </xs:complexType>

    <xs:complexType name="NumericStateVariableType">
        <xs:all>
            <xs:element name="name" type="xs:string"/>
            <xs:element name="value" type="xs:double"/>
        </xs:all>
        
        <xs:attribute name="scaleAndSubsystem" type="ScaleAndSubsystemType"/>
    </xs:complexType>
    
    <!-- User-defined simple types -->

    <xs:simpleType name="NonNegativeDoubleType">
        <xs:restriction base="xs:double">
            <xs:minInclusive value="0"/>
        </xs:restriction>
    </xs:simpleType>
    
    <xs:simpleType name="ScaleAndSubsystemType">
        <xs:restriction base="xs:string">
            <xs:pattern value="[0-9a-zA-Z]+\.[0-9a-zA-Z]+"/>
        </xs:restriction>
    </xs:simpleType>

    /*{% for spatial_measure in spatial_measures %}*/
    <xs:simpleType name="/*{{ spatial_measure.name|first_to_upper }}*/Type">
        <xs:restriction base="xs:double">
            <xs:minInclusive value="/*{{ spatial_measure.min_value }}*/"/>
            <xs:maxInclusive value="/*{{ spatial_measure.max_value }}*/"/>
        </xs:restriction>
    </xs:simpleType>
    
    /*{% endfor %}*/
    <xs:simpleType name="SpatialMetaType">
        <xs:restriction base="xs:string">
        /*{% for spatial_entity in spatial_entities %}*/
            <xs:enumeration value="/*{{ spatial_entity.name }}*/"/>
        /*{% endfor %}*/
        </xs:restriction>
    </xs:simpleType>
</xs:schema>