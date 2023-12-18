#ifndef VDS_SLICE_METADATAHANDLE_HPP
#define VDS_SLICE_METADATAHANDLE_HPP

#include <string>

#include <OpenVDS/OpenVDS.h>

#include "axis.hpp"
#include "boundingbox.hpp"
#include "direction.hpp"

class MetadataHandle {
    friend class DoubleMetadataHandle;
public:
    virtual Axis iline() const noexcept(true) = 0;
    virtual Axis xline() const noexcept(true) = 0;
    virtual Axis sample() const noexcept(true) = 0;
    virtual Axis get_axis(Direction const direction) const noexcept(false) = 0;

    virtual BoundingBox bounding_box() const noexcept(false) = 0;
    virtual std::string crs() const noexcept(false) = 0;
    virtual std::string input_filename() const noexcept(false) = 0;
    virtual std::string import_time_stamp() const noexcept(false) = 0;

    virtual OpenVDS::IJKCoordinateTransformer coordinate_transformer() const noexcept(false) = 0;
protected:
    virtual void dimension_validation() const = 0;
};

class SingleMetadataHandle : public MetadataHandle {
public:
    SingleMetadataHandle(OpenVDS::VolumeDataLayout const* const layout);

    Axis iline() const noexcept(true);
    Axis xline() const noexcept(true);
    Axis sample() const noexcept(true);
    Axis get_axis(Direction const direction) const noexcept(false);

    BoundingBox bounding_box() const noexcept(false);
    std::string crs() const noexcept(false);
    std::string input_filename() const noexcept(false);
    std::string import_time_stamp() const noexcept(false);

    OpenVDS::IJKCoordinateTransformer coordinate_transformer() const noexcept(false);
protected:
    void dimension_validation() const;

private:
    OpenVDS::VolumeDataLayout const* const m_layout;

    Axis m_iline;
    Axis m_xline;
    Axis m_sample;

    int get_dimension(std::vector<std::string> const& names) const;
};

class DoubleMetadataHandle : public MetadataHandle {
public:
    DoubleMetadataHandle(
        MetadataHandle const& handle_A,
        MetadataHandle const& handle_B
    );

    Axis iline() const noexcept(true);
    Axis xline() const noexcept(true);
    Axis sample() const noexcept(true);
    Axis get_axis(Direction const direction) const noexcept(false);

    BoundingBox bounding_box() const noexcept(false);
    std::string crs() const noexcept(false);
    std::string input_filename() const noexcept(false);
    std::string import_time_stamp() const noexcept(false);

    OpenVDS::IJKCoordinateTransformer coordinate_transformer() const noexcept(false);
protected:
    void dimension_validation() const;
private:
    MetadataHandle const* m_handle_A;
    MetadataHandle const* m_handle_B;

    void validate_metadata() const noexcept(false);
};
#endif /* VDS_SLICE_METADATAHANDLE_HPP */
